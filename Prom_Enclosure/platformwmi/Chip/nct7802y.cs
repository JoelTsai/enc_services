/*---------------------------------------------------------------------------**
**          Filename    : NCT7802.cs                                         **
**          Description : Contorl NCT7802 chip                               **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using i2api;



namespace Chip.Contrl
{
    public class NCT7802
    {
        //public PCHSMBUS SMB;
        private static uint[] FAN_install_flag;
        private uint[] FAN_Level;
        private uint Chip_address = 0;
        public NCT7802()
        {
            FAN_install_flag = new uint[2];
            for (int i = 0; i < FAN_install_flag.Length; i++)
                FAN_install_flag[i] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;

        }

        public void Chip_init(uint addr)
        {
            Chip_address = addr;

                uint data = 0x0;
                uint offset = 0x0;
                /* Enable GPIO 5 */
                data = 0x10;
                offset = NCT7802_Constants.NCT7802Y_GPIO_ENABLE_REG;
                if (Nct7802y_write_value(addr, offset, ref data) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");

                }

                /* Set GPIO 5 to output mode */
                data = 0x10;
                offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SEL_REG;
                if (Nct7802y_write_value(addr, offset, ref data) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");

                }

                /* Set fan contorl output type */
                data = 0x0;
                offset = NCT7802_Constants.NCT7802Y_FAN_OUTPUT_TYPE_REG;
                if (Nct7802y_write_value(addr, offset, ref data) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");

                }

                /* Set fan contorl output mode */
                data = 0x0;
                offset = NCT7802_Constants.NCT7802Y_FAN_OUTPUT_MODE_REG;
                if (Nct7802y_write_value(addr, offset, ref data) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");

                }

                data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_START;
                offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
                if (Nct7802y_write_value(addr, offset, ref data) == -1)
                {
                    Console.WriteLine("Nct7802y I2C write fail.\n");
                    
                }

            if (Enclsoure.Enclsoure_class.Model_ID == Enclsoure.Enclsoure_class.Model_VA8100)
            {
                FAN_Level = NCT7802_Constants.NIDEC_FAN_Level;
            }
            // this.SMB = new PCHSMBUS();
            else
            {
                FAN_Level = NCT7802_Constants.DELTA_FAN_Level;
            }
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
               // DebugLogger.WriteLine("NCT7802Y I2C write fail.\n");
                return -1;

            }
            return 0;
        }

        public void Nct7802y_get_fan_speed(uint FanNum, ref uint?[,] Fandata)
        {
            uint offset = 0;
            uint ldata = 0, hdata = 0;
            uint addr;
            uint Fanlevel = 0;
            uint fanCount;
            uint fanSpeed=0;
            uint realFanSpeed = 0;
            byte fail_time = 0;

            addr = NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR;
            while (fail_time < 3)
            {
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
                if (Nct7802y_read_value(addr, offset, ref hdata) == -1)
                {
                    Console.WriteLine("Nct7802y I2C read fail.\n");
                }
                Console.WriteLine("FanNum={0:x} hdata={1:x}.\n", FanNum, hdata);

                offset = NCT7802_Constants.NCT7802Y_FAN_LOW_COUNT_REG;

                if (Nct7802y_read_value(addr, offset, ref ldata) == -1)
                {
                    Console.WriteLine("Nct7802y I2C read fail.\n");
                }
                if (!((hdata == 0xFF) && (ldata == 0xF8)))
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

                    Nct7802y_get_fan_speed_trans(fanSpeed, ref realFanSpeed);
                    if (!(0 < realFanSpeed && realFanSpeed < 600))
                    {
                        break;
                    }
                }
                fail_time++;
                System.Threading.Thread.Sleep(1000);
            }
            if (fail_time >= 3)
            {
                if  ((hdata == 0xFF) && (ldata == 0xF8))
                {
                    fanSpeed = 0;
                    if ((FAN_install_flag[FanNum - 1] & Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED) != Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED)
                    {
                        if ((FAN_install_flag[FanNum - 1] & Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING) != Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING)
                        {
                            Enclsoure.Enclsoure_class.Fan_error += 1;
                            Prom_Enclosure_Serives.Log_File.FileLog("no install +1="+ Enclsoure.Enclsoure_class.Fan_error);
                        }
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_NOT_INSTALLED,
                                              FanNum);
                        FAN_install_flag[FanNum - 1] = Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED;
                        Console.WriteLine("NO install fanerror={0}.", Enclsoure.Enclsoure_class.Fan_error);
                        Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                        Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + FanNum + "]=FAN_NOT_INSTALLED");
                    }
                    Fandata[FanNum - 1, 1] = Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED;
                }
                else
                {
                    if ((FAN_install_flag[FanNum - 1] & Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING) != Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING)
                    {
                        if ((FAN_install_flag[FanNum - 1] & Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED) != Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED)
                        {
                            Prom_Enclosure_Serives.Log_File.FileLog("befoee MALFUNCTIONING +1=" + Enclsoure.Enclsoure_class.Fan_error);
                            Enclsoure.Enclsoure_class.Fan_error += 1;
                            Prom_Enclosure_Serives.Log_File.FileLog("MALFUNCTIONING +1="+Enclsoure.Enclsoure_class.Fan_error);
                        }
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_MALFUNCTIONING,
                                              FanNum);
                        FAN_install_flag[FanNum - 1] = Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING;
                        Console.WriteLine("NO install fanerror={0}.", Enclsoure.Enclsoure_class.Fan_error);
                        Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                        Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + FanNum + "]=FAN_MALFUNCTIONING fanSpeed="+ fanSpeed);
                    }
                    Fandata[FanNum - 1, 1] = Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING;
                }
            }

            else
            {
                if (FAN_install_flag[FanNum - 1] != Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL)
                {
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                          I2connection_Events.EVT_CODE_COOLING_DEVICE_FUNCTIONAL,
                                          FanNum);
                    FAN_install_flag[FanNum-1] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
                    if(Enclsoure.Enclsoure_class.Fan_error!=0)
                         Enclsoure.Enclsoure_class.Fan_error -= 1;
                    Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                    Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + FanNum + "]=FAN_OPERATIONAL");
                }
                Fandata[FanNum - 1, 1] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
            }

            /*get speed level*/
            addr = NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR;

            /* Select bank 0 */
            Nct7802y_set_bank(NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR, NCT7802_Constants.NCT7802Y_BANK_DATA_0);

            /* Get fan speed level */
            switch (FanNum)
            {
                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN0:
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                    break;

                case NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN1:
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                    break;

                default:
                    break;
            }

            if (Nct7802y_read_value(addr, offset, ref Fanlevel) == -1)
            {
                Console.WriteLine("Nct7802y I2C read fail.\n");
            }

            //Nct7802y_get_fan_speed_trans(fanSpeed,ref realFanSpeed);
            //Console.WriteLine("realFanSpeed={0:x}", realFanSpeed);
           /* if (0 < realFanSpeed && realFanSpeed < 600)
            {
                Fandata[FanNum - 1, 1] = Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING;
            }*/


            //Fandata[FanNum-1,0] = (Fanlevel << 16) | (realFanSpeed);
            Fandata[FanNum - 1, 0] = (Fanlevel << 16) | (fanSpeed);
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

            fanlevel = FAN_Level[level];
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


