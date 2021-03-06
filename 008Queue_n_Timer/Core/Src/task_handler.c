#include "main.h"

int extract_command(command_t *cmd);
void process_command(command_t *cmd);

const char *msg_invalid = "////Invalid option////\n";

void menu_task(void* parameters)
{
	uint32_t cmd_addr;
	command_t *cmd;
	int option;

	const char* msg_menu = 	"\n========================\n"
							"|         Menu         |\n"
							"========================\n"
							"LED effect    ----> 0\n"
							"Date and time ----> 1\n"
							"Exit          ----> 2\n"
							"Enter your choice here : ";
	while(1)
	{
		/* Send the menu to the queue to print it */
		xQueueSend(q_print, &msg_menu, portMAX_DELAY);

		/* Wait until a command is received */
		xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);

		cmd = (command_t*)cmd_addr;

		/* Decode the received command */
		if (cmd->length == 1)
		{
			option = cmd->payload[0] - 48;
			switch(option)
			{
				case 0:
					current_state = sLedEffect;
					xTaskNotify(handle_led_task, 0, eNoAction);
					break;
				case 1:
					current_state = sRtcMenu;
					xTaskNotify(handle_rtc_task, 0, eNoAction);
					break;
				case 2:
					break;
				default:
					xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
					continue;
			}
		}else
		{
			xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
			continue;
		}

		/* Task is blocked until a notification is received */
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	}
}

void led_task(void* parameters)
{
	uint32_t cmd_addr;
	command_t *cmd;
	const char* msg_led = "========================\n"
			  	  	  	  "|      LED Effect     |\n"
			  	  	  	  "========================\n"
			  	  	  	  "(none,e1,e2,e3,e4)\n"
			  	  	  	  "Enter your choice here : ";

	while(1)
	{
		/* Task is blocked until command task unblocks it */
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		/* Print the menu for LED effect */
		xQueueSend(q_print, &msg_led, portMAX_DELAY);

		/* Wait until a command is received */
		xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);

		cmd = (command_t*)cmd_addr;

		/* Decode the command */
		if (cmd->length <= 4)
		{
			if ( !strcmp( (char*)cmd->payload, "none" ) )
			{
				led_effect_stop();
			}
			else if ( !strcmp( (char*)cmd->payload, "e1" ) )
			{
				led_effect(1);
			}
			else if ( !strcmp( (char*)cmd->payload, "e2" ) )
			{
				led_effect(2);
			}
			else if ( !strcmp( (char*)cmd->payload, "e3" ) )
			{
				led_effect(3);
			}
			else if ( !strcmp( (char*)cmd->payload, "e4" ) )
			{
				led_effect(4);
			}
			else
			{
				xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
			}
		}else
		{
			xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
		}

		/* Update state variable */
		current_state = sMainMenu;

		/* Notify the menu task */
		xTaskNotify(handle_menu_task, 0, eNoAction);
	}
}

uint8_t get_number(uint8_t *p, int length)
{
	int number;

	if (length > 1)
	{
		/* Convert only the first two char received to integers */
		number = ( ( (p[0] - 48) * 10 ) + (p[1] - 48) );
	}else
	{
		/* Convert char to integer */
		number = p[0] - 48;
	}

	return number;
}

void rtc_task(void* parameters)
{
	const char* msg_rtc1 = "========================\n"
							"|         RTC          |\n"
							"========================\n";

	const char* msg_rtc2 = "Configure Time            ----> 0\n"
							"Configure Date            ----> 1\n"
							"Enable reporting          ----> 2\n"
							"Exit                      ----> 3\n"
							"Enter your choice here : ";


	const char *msg_rtc_hh = "Enter hour(1-12):";
	const char *msg_rtc_mm = "Enter minutes(0-59):";
	const char *msg_rtc_ss = "Enter seconds(0-59):";

	const char *msg_rtc_dd  = "Enter date(1-31):";
	const char *msg_rtc_mo  ="Enter month(1-12):";
	const char *msg_rtc_dow  = "Enter day(1-7 sun:1):";
	const char *msg_rtc_yr  = "Enter year(0-99):";

	const char *msg_conf = "Configuration successful\n";
	const char *msg_rtc_report = "Enable time&date reporting(y/n)?: ";

	uint32_t cmd_addr;
	command_t *cmd;

	int menu_code;

	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	static int rtc_state = 0;

	#define HH_CONFIG 		0
	#define MM_CONFIG 		1
	#define SS_CONFIG 		2

	#define DATE_CONFIG 	0
	#define MONTH_CONFIG 	1
	#define DAY_CONFIG 		2
	#define YEAR_CONFIG 	3

	while(1){
		/* Wait till some task notifies */
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		/* Print the menu and show current date and time information */
		xQueueSend(q_print, &msg_rtc1, portMAX_DELAY);
		show_time_date();
		xQueueSend(q_print, &msg_rtc2, portMAX_DELAY);


		while(current_state != sMainMenu){

			/* Wait for command notification */
			xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);

			cmd = (command_t*)cmd_addr;

			switch(current_state)
			{
				case sRtcMenu:{

					/* Process RTC menu commands */
					if (cmd->length == 1)
					{
						menu_code = cmd->payload[0] - 48;
						switch (menu_code)
						{
							case 0:
								current_state = sRtcTimeConfig;
								xQueueSend(q_print, &msg_rtc_hh, portMAX_DELAY);
								break;
							case 1:
								current_state = sRtcDateConfig;
								xQueueSend(q_print, &msg_rtc_dd, portMAX_DELAY);
								break;
							case 2:
								current_state = sRtcReport;
								xQueueSend(q_print, &msg_rtc_report, portMAX_DELAY);
								break;
							case 3:
								current_state = sMainMenu;
								break;
							default:
								current_state = sMainMenu;
								xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
						}
					}else
					{
						current_state = sMainMenu;
						xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
					}
					break;
				}

				case sRtcTimeConfig:{
					switch (rtc_state)
					{
						case HH_CONFIG:{
							/* Get the hour sent by the user */
							uint8_t hour = get_number(cmd->payload, cmd->length);
							time.Hours = hour;
							rtc_state = MM_CONFIG;
							xQueueSend(q_print, &msg_rtc_mm, portMAX_DELAY);
							break;}
						case MM_CONFIG:{
							/* Get the minutes sent by the user */
							uint8_t minute = get_number(cmd->payload, cmd->length);
							time.Minutes = minute;
							rtc_state = SS_CONFIG;
							xQueueSend(q_print, &msg_rtc_ss, portMAX_DELAY);
							break;}
						case SS_CONFIG:{
							/* Get the seconds sent by the user */
							uint8_t second = get_number(cmd->payload, cmd->length);
							time.Seconds = second;

							/* Validate that all the time information is valid */
							if ( !validate_rtc_information(&time, NULL) )
							{
								rtc_configure_time(&time);
								xQueueSend(q_print, &msg_conf, portMAX_DELAY);
								show_time_date();
							}else
							{
								xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
							}

							/* Return to main menu */
							current_state = sMainMenu;
							rtc_state = 0;
							break;}
					}

					break;
				}

				case sRtcDateConfig:{
					switch (rtc_state)
					{
						case DATE_CONFIG:{
							/* Get the day sent by the user */
							uint8_t d = get_number(cmd->payload, cmd->length);
							date.Date = d;
							rtc_state = MONTH_CONFIG;
							xQueueSend(q_print, &msg_rtc_mo, portMAX_DELAY);
							break;}
						case MONTH_CONFIG:{
							/* Get the month sent by the user */
							uint8_t month = get_number(cmd->payload, cmd->length);
							date.Month = month;
							rtc_state = DAY_CONFIG;
							xQueueSend(q_print, &msg_rtc_dow, portMAX_DELAY);
							break;}
						case DAY_CONFIG:{
							/* Get the day of week sent by the user */
							uint8_t day = get_number(cmd->payload, cmd->length);
							date.WeekDay = day;
							rtc_state = YEAR_CONFIG;
							xQueueSend(q_print, &msg_rtc_yr, portMAX_DELAY);
							break;}
						case YEAR_CONFIG:{
							/* Get the year sent by the user */
							uint8_t year = get_number(cmd->payload, cmd->length);
							date.Year = year;

							/* Validate that all the date information is valid */
							if ( !validate_rtc_information(NULL, &date) )
							{
								rtc_configure_date(&date);
								xQueueSend(q_print, &msg_conf, portMAX_DELAY);
								show_time_date();
							}else
							{
								xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
							}

							/* Return to main menu */
							current_state = sMainMenu;
							rtc_state = 0;
							break;}
					}

					break;}

				case sRtcReport:{
					break;}

			}

		}

		/* Notify menu task */
		xTaskNotify(handle_menu_task, 0, eNoAction);
		}
}

void print_task(void* parameters)
{
	uint32_t *msg;

	while(1)
	{
		xQueueReceive(q_print, &msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen((char*)msg), HAL_MAX_DELAY);
	}
}

void command_task(void* parameters)
{
	BaseType_t status;
	command_t cmd;

	while(1)
	{
		/* Wait indefinitely for a notification */
		status = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
		if (status == pdTRUE)
		{
			process_command(&cmd);
		}
	}
}

void process_command(command_t *cmd)
{
	extract_command(cmd);

	switch(current_state)
	{
		case sMainMenu:
			xTaskNotify(handle_menu_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;
		case sLedEffect:
			xTaskNotify(handle_led_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;
		case sRtcMenu:
		case sRtcDateConfig:
		case sRtcTimeConfig:
		case sRtcReport:
			xTaskNotify(handle_rtc_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;
	}
}

int extract_command(command_t *cmd)
{
	uint8_t item;
	BaseType_t status;

	/* Returns if there are no messages in the queue */
	status = uxQueueMessagesWaiting(q_data);
	if (!status) return -1;

	uint8_t i = 0;
	do
	{
		status = xQueueReceive(q_data, &item, 0);
		if (status == pdTRUE)	cmd->payload[i++] = item;
	}while(item != '\n');
	cmd->payload[i-1] = '\0';
	cmd->length = i - 1;

	return 0;
}
