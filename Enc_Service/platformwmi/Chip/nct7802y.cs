/*---------------------------------------------------------------------------**
**          Filename    : NCT7802.cs                                         **
**          Description : Contorl NCT7802 chip                               **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using System.Threading;
using System.Globalization;
using System.Text;
using Enc_Service.platformwmi;
using i2api;



namespace Chip.Contrl
{

    static class NCT7802_Constants
    {

        //public const uint[,] NCT7802Y_ENV_CTRL_FAN_MATRIX = { NIDEC, SYSTEM_FAN , {0x0F,0x1F,0x2F,0x3F,0x4F,0x5F,0x6F,0x7F,0x8F,0x9F,0xAF,0xBF,0xCF,0xDF,0xEF,0xFE}};
        internal static readonly uint[] FAN_Level = { 0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFE };

        internal const uint BLEN = 1;
        internal const uint WLEN = 2;
        internal const uint DWLEN = 4;


        internal const uint NCT7802Y_I2C_SUCCESS = 0;
        internal const uint NCT7802Y_I2C_FAILURE = 1;

        internal const uint NCT7802Y_PSU_LED_INIT = 0x0A;
        //internal const uint NCT7802Y_BP_HW_MONITOR_ADDR     = 0x2C;
        internal const uint NCT7802Y_BP_HW_MONITOR_ADDR = 0x2E;
        internal const uint NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR = 0x28;

        internal const uint PCA955A_READ_PORT_0 = 0x00;
        internal const uint PCA955A_READ_PORT_1 = 0x01;
        internal const uint PCA955A_WRITE_PORT_0 = 0x02;
        internal const uint PCA955A_WRITE_PORT_1 = 0x03;
        internal const uint PCA955A_CONFIG_PORT_0 = 0x06;
        internal const uint PCA955A_CONFIG_PORT_1 = 0x07;

        //
        internal const uint NCT7802Y_PSU_INITIAL_FAN_SPEED_LEVEL = 8;

        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_1 = (0x54 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_2 = (0x50 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_3 = (0x56 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_4 = (0x4C >> 1);

        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_W_1 = (0x72 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_R_1 = (0x73 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_W_2 = (0x74 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_R_2 = (0x75 >> 1);


        /* ID */
        internal const uint NCT7802Y_SUPERIO_CHIP_ID_REG = 0xFE;

        /* BP VPD */
        internal const uint NCT7802Y_BP_VPD = 0x51;

        /* 1U4 */
        /* fan */
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN0 = 0x00;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN1 = 0x01;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN2 = 0x02;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN3 = 0x03;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN_ALL = 0xFF;

        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_SPEED_UNDER_MAX = 20000;
        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_MAX_LEVEL = 0xFE;
        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_SPIN_STABLE = 5;

        /* Device count */
        internal const uint NCT7802Y_1U4_BP_FAN_DEVICE_CNT = 0x04;

        /* 2U6 */
        /* fan */
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN0 = 0x00;
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN1 = 0x01;
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN_ALL = 0xFF;

        /* 2U8 */
        /* fan */
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN0 = 0x01;
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN1 = 0x02;
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN_ALL = 0xFF;

        /* fan fan control pin unplug */
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_SPEED_UNDER_MAX = 7000;
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_MAX_LEVEL = 0x7F;
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_SPIN_STABLE = 5;
        //
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_SPEED_UNDER_MAX = 10000;
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_MAX_LEVEL = 0x7F;
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_SPIN_STABLE = 5;



        /* Device count */
        internal const uint NCT7802Y_2U6_BP_FAN_DEVICE_CNT = 0x02;

        internal const uint NCT7802Y_PWR_BUTTON_NOPRESS = 0x01;
        internal const uint NCT7802Y_PWR_BUTTON_PRESS = 0x00;


        /* Configuration register */
        internal const uint NCT7802Y_CONFIG_RESET_REG = 0xFC;
        internal const uint NCT7802Y_CONFIG_RESET_DATA_STOP = 0x80;
        internal const uint NCT7802Y_CONFIG_START_REG = 0x21;
        internal const uint NCT7802Y_CONFIG_DATA_STOP = 0x00;
        internal const uint NCT7802Y_CONFIG_DATA_START = 0x01;

        /* Bank 0 */
        internal const uint NCT7802Y_BANK_SEL_REG = 0x00;
        internal const uint NCT7802Y_BANK_DATA_0 = 0;
        internal const uint NCT7802Y_BANK_DATA_1 = 1;

        /* GPIO */
        internal const uint NCT7802Y_GPIO_MODE_SELECT_REG = 0x22;
        internal const uint NCT7802Y_GPIO_FAN_ENABLE_REG = 0x24;
        internal const uint NCT7802Y_GPIO_ENABLE_REG = 0x55;
        internal const uint NCT7802Y_GPIO_MODE_SEL_REG = 0x56;
        internal const uint NCT7802Y_GPIO_OUTPUT_TYPE_REG = 0x57;
        internal const uint NCT7802Y_GPIO_INPUT_DATA_REG = 0x58;
        internal const uint NCT7802Y_GPIO_OUTPUT_DATA_REG = 0x59;
        internal const uint NCT7802Y_TEMP_DETECT_RATE = 0x26;
        internal const uint NCT7802Y_TEMP_FILTER_RATE = 0xCB;

        /* Voltage */
        internal const uint NCT7802Y_VOLT_ENABLE_REG = 0x25;
        internal const uint NCT7802Y_VOLT_VSEN1_H_REG = 0x0C;
        internal const uint NCT7802Y_VOLT_VSEN2_H_REG = 0x0D;
        internal const uint NCT7802Y_VOLT_VSEN3_H_REG = 0x0E;
        internal const uint NCT7802Y_VOLT_VCORE_H_REG = 0x0A;
        internal const uint NCT7802Y_VOLT_LOW_REG = 0x0F;
        internal const uint NCT7802Y_VOLT_VCC_REG = 0x09;

        /* Temperature */
        internal const uint NCT7802Y_TEMP_RTD2_HIGH_REG = 0x02;
        internal const uint NCT7802Y_TEMP_RTD3_HIGH_REG = 0x03;
        internal const uint NCT7802Y_TEMP_TR1_HIGH_REG = 0x01;
        internal const uint NCT7802Y_TEMP_TD2_REG = 0x02;
        internal const uint NCT7802Y_TEMP_TD_REG = 0x04;
        internal const uint NCT7802Y_TEMP_TD3_REG = 0x03;
        internal const uint NCT7802Y_TEMP_TD_LOW_REG = 0x05;
        internal const uint NCT7802Y_TEMP_TR2_OFFSET_REG = 0xC5;
        internal const uint NCT7802Y_TEMP_TR3_OFFSET_REG = 0xC6;

        /* Fan */
        internal const uint NCT7802Y_FAN_IN1_COUNT_REG = 0x10;
        internal const uint NCT7802Y_FAN_IN2_COUNT_REG = 0x11;
        internal const uint NCT7802Y_FAN_IN3_COUNT_REG = 0x12;
        internal const uint NCT7802Y_FAN_LOW_COUNT_REG = 0x13;
        internal const uint NCT7802Y_FAN_OUTPUT_TYPE_REG = 0x5E;
        internal const uint NCT7802Y_FAN_OUTPUT_MODE_REG = 0x5F;
        internal const uint NCT7802Y_FAN_FANCTL1_REG = 0x60;
        internal const uint NCT7802Y_FAN_FANCTL2_REG = 0x61;
        internal const uint NCT7802Y_FAN_FANCTL3_REG = 0x62;

        /* GPIO MASK */
        internal const uint NCT7802Y_GPIO1_MASK = 0x01;
        internal const uint NCT7802Y_GPIO2_MASK = 0x02;
        internal const uint NCT7802Y_GPIO3_MASK = 0x04;
        internal const uint NCT7802Y_GPIO4_MASK = 0x08;
        internal const uint NCT7802Y_GPIO5_MASK = 0x10;
        internal const uint NCT7802Y_GPIO6_MASK = 0x20;
        internal const uint NCT7802Y_GPIO7_MASK = 0x40;
        internal const uint NCT7802Y_GPIO8_MASK = 0x80;

        /* GPIO BIT */
        internal const uint NCT7802Y_GPIO_BIT_0 = 0;
        internal const uint NCT7802Y_GPIO_BIT_1 = 1;
        internal const uint NCT7802Y_GPIO_BIT_2 = 2;
        internal const uint NCT7802Y_GPIO_BIT_3 = 3;
        internal const uint NCT7802Y_GPIO_BIT_4 = 4;
        internal const uint NCT7802Y_GPIO_BIT_5 = 5;
        internal const uint NCT7802Y_GPIO_BIT_6 = 6;
        internal const uint NCT7802Y_GPIO_BIT_7 = 7;

        internal const uint SANYO = 0;
        internal const uint SUNON = 1;
        internal const uint REGO = 2;
        internal const uint NIDEC = 3;
        internal const uint DELTA = 4;

        internal const uint SYSTEM_FAN = 0;
        internal const uint CPU_FAN = 1;

        internal const uint NCT7802Y_MAX_FAN_MATRIX = 3;

    }//end of Constants

    public class NCT7802
    {
        //public PCHSMBUS SMB;
        private static bool FAN_install_flag = false;

        public NCT7802()
        {
           // this.SMB = new PCHSMBUS();

        }

        public int Nct7802y_write_value(uint addr, uint reg, ref uint data)
        {
            // return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
            uint[] data_temp = { data };
            return PCHSMBUS.WriteSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
        }

        public int Nct7802y_read_value(uint addr, uint reg, ref uint data)
        {

            //return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
            int ret;
            uint[] data_temp = { data };
            ret = PCHSMBUS.ReadSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
            data = data_temp[0];
            return ret;

        }

        public int Nct7802y_set_bank(uint addr, uint data)
        {

            if (Nct7802y_write_value(addr, NCT7802_Constants.NCT7802Y_BANK_SEL_REG, ref data) == -1)
            {
                DebugLogger.WriteLine("NCT7802Y I2C write fail.\n");
                return -1;

            }
            return 0;
        }

        public void Nct7802y_get_fan_speed(uint FanNum, ref uint?[] Fandata)
        {
            uint offset = 0;
            uint  ldata, hdata;
            uint addr;
            uint Fanlevel = 0;
            uint fanCount;
            uint fanSpeed;
            addr = NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR;
            Nct7802y_set_bank(NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR, NCT7802_Constants.NCT7802Y_BANK_DATA_0);


            switch (FanNum)
            {
                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN0:
                    offset = NCT7802_Constants.NCT7802Y_FAN_IN1_COUNT_REG;
                    break;

                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN1:
                    offset = NCT7802_Constants.NCT7802Y_FAN_IN2_COUNT_REG;
                    break;

                default:
                    break;
            }

            hdata = 0;
            if (Nct7802y_read_value(addr, offset, ref hdata) == -1)
            {
                Console.WriteLine("Nct7802y I2C read fail.\n");
            }

            ldata = 0;
            offset = NCT7802_Constants.NCT7802Y_FAN_LOW_COUNT_REG;

            if (Nct7802y_read_value(addr, offset, ref ldata) == -1)
            {
                Console.WriteLine("Nct7802y I2C read fail.\n");
            }

            if ((hdata == 0xFF) && (ldata == 0xF8))
            {
                fanSpeed = 0;
                if (FAN_install_flag == false)
                {
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                          I2connection_Events.EVT_CODE_COOLING_DEVICE_NOT_INSTALLED,
                                          1);
                    FAN_install_flag = true;
                }
            }

            else
            {
                fanCount = (hdata << 5) | (ldata >> 3);
                if (fanCount != 0)
                {
                    fanSpeed = (fanCount >> 4);
                }
                else
                {
                    fanSpeed = 0;
                }
                if (FAN_install_flag == true)
                {
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                          I2connection_Events.EVT_CODE_COOLING_DEVICE_FUNCTIONAL,
                                          1);
                    FAN_install_flag = false;
                }
            }

            /*get speed level*/
            addr = NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR;

            /* Select bank 0 */
            Nct7802y_set_bank(NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR, NCT7802_Constants.NCT7802Y_BANK_DATA_0);

            /* Get fan speed level */
            switch (FanNum)
            {
                case NCT7802_Constants.NCT7802Y_2U6_BP_DEVICE_FAN0:
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                    break;

                case NCT7802_Constants.NCT7802Y_2U6_BP_DEVICE_FAN1:
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                    break;

                default:
                    break;
            }

            if (Nct7802y_read_value(addr, offset, ref Fanlevel) == -1)
            {
                Console.WriteLine("Nct7802y I2C read fail.\n");
            }

            Fandata[0] = (Fanlevel << 16) | (fanSpeed);
        }

        public void Nct7802y_get_fan_speed_trans(uint fanSpeed, ref uint realFanSpeed)
        {
            /* LOCAL VARIABLES DECLARATION
             */


            /* BODY
             */
            if (fanSpeed != 0 && fanSpeed != 255)
            {
                realFanSpeed = ((1350 * 1000) / (fanSpeed * 16));
            }
            else
            {
                realFanSpeed = 0;
            }

            return;
        }

        public void Nct7802y_set_fan_speed(uint fanNum, uint level)
        {
            //Enc_Service.Enc_Service.FileLog("Nct7802y_set_fan_speed");
            uint offset1 = 0;
            uint offset2 = 0;
            uint fanlevel = 0;
            uint addr;

            addr = NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR;

            Nct7802y_set_bank(NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR, NCT7802_Constants.NCT7802Y_BANK_DATA_0);

            switch (fanNum)
            {
                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN0:
                    offset1 = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                    break;

                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN1:
                    offset1 = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                    break;

                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL:
                    offset1 = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                    offset2 = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                    break;

                default:
                    break;
            }
            //Enc_Service.Enc_Service.FileLog("level="+level);

            fanlevel = NCT7802_Constants.FAN_Level[level];
            //Enc_Service.Enc_Service.FileLog("fanlevel="+fanlevel);
            //fanlevel = level;
            Console.WriteLine("  level =  : 0x{0:x}", fanlevel);
            if (Nct7802y_write_value(addr, offset1, ref fanlevel) == -1)
            {
                Console.WriteLine("Nct7802y I2C write fail.\n");
            }

            if (fanNum == NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL)
            {
                if (Nct7802y_write_value(addr, offset2, ref fanlevel) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");
                }
            }
        }
    }
}


