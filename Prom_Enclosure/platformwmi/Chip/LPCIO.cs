/*---------------------------------------------------------------------------**
**          Filename    : NCT6776.cs                                         **
**          Description : Contorl NCT chip                                   **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/

using System;
using i2api;
using WingRing;


namespace Chip.Contrl
{

    static class NCT5567_Constants
    {

        internal const uint NCT5567_ENV_CTRL_FAN_SEN_CPUTIN = 0;
        internal const uint NCT5567_ENV_CTRL_FAN_SEN_SYSTIN = 1;
        internal const uint NCT5567_ENV_CTRL_FAN_SEN_AUXTIN = 2;
        internal const uint NCT5567_ENV_CTRL_FAN_ALL = 0xFF;

        internal const uint NCT5567_ENV_FAN_CONFIG_SYSFAN_REG = 0x004;
        internal const uint NCT5567_ENV_FAN_CONFIG_FAN_PWM = 0x000;
        internal const uint NCT5567_ENV_FAN_MODE_SYSFAN_REG = 0x102;
        internal const uint NCT5567_ENV_FAN_MODE_CPUFAN_REG = 0x202;
        internal const uint NCT5567_ENV_FAN_MODE_AUXFAN_REG = 0x302;
        internal const uint NCT5567_ENV_FAN_MODE_AUXFAN2_REG = 0x902;
        internal const uint NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE = 0x000;
        internal const ushort NCT5567_ENV_FAN_SET_SYSFAN_REG = 0x109;
        internal const ushort NCT5567_ENV_FAN_SET_CPUFAN_REG = 0x209;
        internal const ushort NCT5567_ENV_FAN_SET_AUXFAN_REG = 0x309;
        internal const ushort NCT5567_ENV_FAN_SET_AUXFAN2_REG = 0x909;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_VAL_H_REG = 0x4C0;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_VAL_L_REG = 0x4C1;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_VAL_H_REG = 0x4C2;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_VAL_L_REG = 0x4C3;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_VAL_H_REG = 0x4C4;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_VAL_L_REG = 0x4C5;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_VAL_H_REG = 0x4C8;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_VAL_L_REG = 0x4C9;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_COUNT_H_REG = 0x4B0;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_COUNT_L_REG = 0x4B1;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_COUNT_H_REG = 0x4B2;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_COUNT_L_REG = 0x4B3;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_COUNT_H_REG = 0x4B4;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_COUNT_L_REG = 0x4B5;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_H_REG = 0x4B8;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_L_REG = 0x4B9;

        internal const uint NCT5567_ENV_VOLT_CONFIG_VBAT_ENABLE = 0x01;
        internal const uint NCT5567_ENV_VOLT_CONFIG_VBAT_REG = 0x05D;

        /* Need to check
         * internal const uint NCT5567_ENV_VOLT_CPUCORE_REG = 0x480;
        internal const uint Nct6776_ENV_VOLT_12V_REG = 0x021;
        internal const uint Nct6776_ENV_VOLT_AVCC_REG = 0x022;
        internal const uint Nct6776_ENV_VOLT_3VCC_REG = 0x023;
        internal const uint Nct6776_ENV_VOLT_VIN1_REG = 0x024;
        internal const uint Nct6776_ENV_VOLT_5V_REG = 0x025;
        internal const uint Nct6776_ENV_VOLT_VIN3_REG = 0x026;
        */
        internal const uint NCT5567_ENV_VOLT_3VSB_REG = 0x487;
        internal const uint NCT5567_ENV_VOLT_VBAT_REG = 0x488;

        internal const byte NCT5567_DEV = 0x07;

        internal const uint NCT6XXX_PARALLEL_PORT_LDN = 0x01;
        internal const uint NCT6XXX_UART_A_LDN = 0x02;
        internal const uint NCT6XXX_UART_B_LDN = 0x03;
        internal const uint NCT6XXX_GPIO_LDN = 0x07;
        internal const uint NCT6XXX_PME_LDN = 0x04;
        internal const uint NCT6XXX_HW_MONITOR_LDN = 0x0B;
        internal const uint NCT6XXX_GPIO_WDT1_LDN = 0x08;
        internal const uint NCT6XXX_PARALLEL_VID_LDN = 0x0D;

        internal const uint NCT5567_ENV_CTRL_BASE_ADDR_REG = 0x60;

        internal static readonly uint[] FAN_Level = { 0x4A, 0x4F, 0x5A, 0x5F, 0x6A, 0x6F, 0x7A, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF };


        internal const byte CHIP_ID_REGISTER = 0x20;
        internal const byte CHIP_REVISION_REGISTER = 0x21;
        internal const byte BASE_ADDRESS_REGISTER = 0x60;
    }

    public class NCT677X 
    {
    	private uint port;
        public static uint LPCIO_ID;
		private const ushort NUVOTON_VENDOR_ID = 0x5CA3;
		private readonly ushort registerPort = 0x2E;
		private readonly ushort valuePort = 0x2F;
	
	// Hardware Monitor Registers	 
		//private readonly ushort VENDOR_ID_HIGH_REGISTER;
		//private readonly ushort VENDOR_ID_LOW_REGISTER;
		private const uint ADDRESS_REGISTER_OFFSET = 0x05;
		private const uint DATA_REGISTER_OFFSET = 0x06;
		private const byte BANK_SELECT_REGISTER = 0x4E;

        private ushort[] voltageRegisters;
        private VoltageType[] voltageTypes;

		private ushort[] FanRegisters;
		private ushort[] FanRegisters_high;
		private ushort[] FanRegisters_low;
		private ushort[] TemperatureRegisters;

        public static uint SIO_FAN_NUM=1;
        public static uint SIO_TEM_NUM = 1;

        public static uint CPU_Fan_Level = 0;
        public static uint SYS_Fan_Level = 0;
        public static uint AUX_Fan_Level = 0;

        private static readonly uint FAN_offset = 0x03;//this offset is the level different of SYS_FAN and CPU_FAN

        private static uint[] FAN_install_flag;

        private static uint NCT6791 = 0xC803;
        private static uint NCT6776 = 0xC333;
        private static uint NCT5567 = 0xD121;
        //fasle for normal true for non-install;

        public NCT677X()
      	{	

            //Ring0.Open();
            NCT_init();

            // Control Fan in Manual Mode
            if(LPCIO_ID!= NCT6791)
            {
                WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_MODE_SYSFAN_REG, NCT5567_Constants.NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE);
                WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_MODE_CPUFAN_REG, NCT5567_Constants.NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE);
                WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_MODE_AUXFAN_REG, NCT5567_Constants.NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE);
                WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_MODE_AUXFAN2_REG, NCT5567_Constants.NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE);
            }
            /*
             // Enable temperature sensor 
            tmp = nct6XXX_read_value(Nct6776_ENV_TEMP_CONFIG_TEMP0_REG);
            if (tmp & Nct6776_ENV_TEMP_CONFIG_MASK)
            {
                nct6XXX_write_value(Nct6776_ENV_TEMP_CONFIG_TEMP0_REG, tmp & 0xfe);
            }

            tmp = nct6XXX_read_value(Nct6776_ENV_TEMP_CONFIG_TEMP1_REG);
            if (tmp & Nct6776_ENV_TEMP_CONFIG_MASK)
            {
                nct6XXX_write_value(Nct6776_ENV_TEMP_CONFIG_TEMP1_REG, tmp & 0xfe);
            }

            tmp = nct6XXX_read_value(Nct6776_ENV_TEMP_CONFIG_TEMP2_REG);
            if (tmp & Nct6776_ENV_TEMP_CONFIG_MASK)
            {
                nct6XXX_write_value(Nct6776_ENV_TEMP_CONFIG_TEMP2_REG, tmp & 0xfe);
            }

            // Enable VBAT sensor 
            nct6XXX_write_value(Nct6776_ENV_VOLT_CONFIG_VBAT_REG, (u8)(Nct6776_ENV_VOLT_CONFIG_VBAT_ENABLE));
           
            // Enable super io hw monitor 
            tmp = nct6XXX_read_value(NCT6XXX_ENV_HWM_CONFIG_REG);
            tmp |= NCT6XXX_ENV_HWM_CONFIG_START;
            nct6XXX_write_value(NCT6XXX_ENV_HWM_CONFIG_REG, (u8)tmp);
            */
            SIO_FAN_NUM = Convert.ToUInt32(FanRegisters.Length);
            FAN_install_flag = new uint[SIO_FAN_NUM];
            for (int i = 0; i < SIO_FAN_NUM; i++)
                FAN_install_flag[i] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
        }

        private void NCT_init()
        {
            
            WinbondNuvotonFintekEnter();
            Nct6XXX_LDN_select(NCT5567_Constants.NCT6XXX_HW_MONITOR_LDN);

            LPCIO_ID=Readword(NCT5567_Constants.CHIP_ID_REGISTER);
            if (LPCIO_ID == 0xD121)
            {
                    // For NCT5567
                    // - 1V    => reg : 0x480
                    // - 5V    => reg : 0x48D
                    // - 12V   => reg : 0x48C
                    // - 3.3V  => reg : 0x483
                    voltageRegisters = new ushort[] { 0x480, 0x48D, 0x48C, 0x483 };
                if (Enclsoure.Enclsoure_class.Model_ID != Enclsoure.Enclsoure_class.Model_VA8020)
                {
                    FanRegisters = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_SET_CPUFAN_REG };
                    FanRegisters_high = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_GET_CPUFAN_COUNT_H_REG };
                    FanRegisters_low = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_GET_CPUFAN_COUNT_L_REG };
                }
                else
                {
                    FanRegisters = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_SET_CPUFAN_REG, NCT5567_Constants.NCT5567_ENV_FAN_SET_SYSFAN_REG };//, NCT5567_Constants.NCT5567_ENV_FAN_SET_AUXFAN2_REG };
                    FanRegisters_high = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_GET_CPUFAN_COUNT_H_REG, NCT5567_Constants.NCT5567_ENV_FAN_GET_SYSFAN_COUNT_H_REG };//, NCT5567_Constants.NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_H_REG };
                    FanRegisters_low = new ushort[] { NCT5567_Constants.NCT5567_ENV_FAN_GET_CPUFAN_COUNT_L_REG, NCT5567_Constants.NCT5567_ENV_FAN_GET_SYSFAN_COUNT_L_REG };//, NCT5567_Constants.NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_L_REG };
                }
                    TemperatureRegisters = new ushort[] { 0x492 };
                SIO_TEM_NUM = Convert.ToUInt32(TemperatureRegisters.Length);
            }

            else if (LPCIO_ID == 0xC333)
            {
                // For NCT6776
                // - 1V    => reg : 0x20
                // - 5V    => reg : 0x26
                // - 12V   => reg : 0x25
                // - 3.3V  => reg : 0x23
                voltageRegisters = new ushort[] { 0x020, 0x026, 0x025, 0x023 };
            }
            else if (LPCIO_ID == 0xC803)//the model of 6600
            {
                // For NCT6791
                // - 1V    => reg : 0x20
                // - 5V    => reg : 0x26
                // - 12V   => reg : 0x25
                // - 3.3V  => reg : 0x23
                ///////////need to modify
                voltageRegisters = new ushort[] { 0x480, 0x481, 0x484, 0x483 };
                FanRegisters = new ushort[] { 0x001 };
                FanRegisters_high = new ushort[] { 0x4C2 };
                FanRegisters_low = new ushort[] { 0x4C3 };
                TemperatureRegisters = new ushort[] { 0x073,0x027,0x150 };
                ///////////

                SIO_TEM_NUM = Convert.ToUInt32(TemperatureRegisters.Length);
                Enclsoure.Enclsoure_class.Model_ID = 0xFFFF;
                Console.WriteLine("the chip =0xffff");
            }

            port = Readword(NCT5567_Constants.NCT5567_ENV_CTRL_BASE_ADDR_REG);
            Nct6XXX_exit();

        }
        public void Get_Fan(ref uint?[,] Fan)
		{
			
			int fans = 0;
			int fanCount = 0;
            uint realFanSpeed = 0;
            int FanSpeed = 0;
            for (int i = 0; i < FanRegisters.Length; i++)
            {
				int Fan_Level = ReadByte(FanRegisters[i]);
                byte Speed_high = 0; // = ReadByte(FanRegisters_high[i]); // CPU fan Speed
                byte Speed_low = 0;  // = ReadByte(FanRegisters_low[i]);
                byte fail_time = 0;


                while(fail_time<3)
                {
                    
                    Speed_high = ReadByte(FanRegisters_high[i]); // CPU fan Speed
                    Speed_low = ReadByte(FanRegisters_low[i]);
                    if (!((Speed_high == 0xFF) && (Speed_low == 0x1F)))
                    {
                        fanCount = (Speed_high << 5) + (Speed_low & 0x1F);
                        FanSpeed = fanCount >> 4;
                        NCT_get_fan_speed_trans(Convert.ToUInt32(FanSpeed), ref realFanSpeed);
                        fans = (Fan_Level << 16) | (FanSpeed);
                        if (!(0 < realFanSpeed && realFanSpeed < 600))
                        {
                            break;
                        }
                    }
                    fail_time++;
                    System.Threading.Thread.Sleep(1000);
                }


				byte data_tmp = ReadByte(FanRegisters[i]); // controller temperature
				


                if (Enclsoure.Enclsoure_class.Model_ID != 0xFFFF)
                {
                    if (fail_time>=3)
                    {
                        fans = 0;
                        if ((Speed_high == 0xFF) && (Speed_low == 0x1F))
                        {
                            if ((Fan[i, 1] & Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED) != Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED)
                            {
                                if ((Fan[i, 1] & Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING) != Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING)
                                {
                                    Enclsoure.Enclsoure_class.Fan_error += 1;
                                }
                                I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                                      I2connection_Events.EVT_CODE_COOLING_DEVICE_NOT_INSTALLED,
                                                      Convert.ToUInt16(i));
                                FAN_install_flag[i] = Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED;
                                Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                                Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + i + "]=FAN_NOT_INSTALLED");
                            }
                            Fan[i, 1] = Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED;
                        }
                        else
                        {
                            if ((Fan[i, 1] & Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING) != Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING)
                            {
                                if ((Fan[i, 1] & Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED) != Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED)
                                {
                                    Enclsoure.Enclsoure_class.Fan_error += 1;
                                }
                                I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                                      I2connection_Events.EVT_CODE_COOLING_DEVICE_MALFUNCTIONING,
                                                      Convert.ToUInt16(i));
                                FAN_install_flag[i] = Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING;
                                Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                                Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + i + "]=FAN_MALFUNCTIONING fanSpeed="+ FanSpeed);
                            }
                            Fan[i, 1] = Enclsoure.Enclsoure_Constants.FAN_MALFUNCTIONING;
                        }
                    }
                    else
                    {
                      //  fanCount = (Speed_high << 5) + (Speed_low & 0x1F);
                       // FanSpeed = fanCount >> 4;
                       // NCT_get_fan_speed_trans(Convert.ToUInt32(FanSpeed), ref realFanSpeed);
                       // fans = (Fan_Level << 16) | (Convert.ToInt16(realFanSpeed));
                        
                        if ((Fan[i, 1] != Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL))
                        {
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                                  I2connection_Events.EVT_CODE_COOLING_DEVICE_FUNCTIONAL,
                                                  Convert.ToUInt16(i));
                            FAN_install_flag[i] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
                            if (Enclsoure.Enclsoure_class.Fan_error != 0)
                                Enclsoure.Enclsoure_class.Fan_error -= 1;
                            Enclsoure.Enclsoure_class.FAN_LED_trigger = true;
                            Prom_Enclosure_Serives.Log_File.FileLog("Fan[" + i + "]=FAN_OPERATIONAL");
                        }
                        Fan[i, 1] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
                    }
                    Fan[i, 0] = Convert.ToUInt32(fans);
                }
                else
                {
                    FanSpeed = (Speed_high << 8) | Speed_low;
                    Console.WriteLine("FANSPEEM={0}", FanSpeed);
                    Fan[i, 0] = Convert.ToUInt32(FanSpeed);
                    Fan[i, 1] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
                }
			}
            

		}

        public void NCT_get_fan_speed_trans(uint fanSpeed, ref uint realFanSpeed)
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

        public void Set_Fan(uint fanNum, uint level)
        {
            uint fanlevel = 0;

           // Console.WriteLine("fanNum =  0x{0:x}", fanNum);
            switch (fanNum)
            {
                case NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_CPUTIN:
                    level += FAN_offset;//offset
                    level= (level > 15) ?  15 : level;
                    fanlevel = NCT5567_Constants.FAN_Level[level];
                    //fanlevel = level;
                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_CPUFAN_REG, fanlevel);
                    CPU_Fan_Level = level;
                    break;

                case NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_SYSTIN:
                    fanlevel = NCT5567_Constants.FAN_Level[level];
                    //fanlevel = level;
                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_SYSFAN_REG, fanlevel);
                    SYS_Fan_Level = level;
                    break;

                case NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_AUXTIN:
                    fanlevel = NCT5567_Constants.FAN_Level[level];
                   // fanlevel = level;
                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_AUXFAN2_REG, fanlevel);
                    AUX_Fan_Level = level;
                    break;

                case NCT5567_Constants.NCT5567_ENV_CTRL_FAN_ALL:
                    fanlevel = NCT5567_Constants.FAN_Level[level];
                    //fanlevel = level;
                    //CPU_Fan_Level = fanlevel;
                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_CPUFAN_REG, fanlevel);

                    //fanlevel = NCT6776_Constants.FAN_Level[level];

                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_SYSFAN_REG, fanlevel);
                    WriteByte(NCT5567_Constants.NCT5567_ENV_FAN_SET_AUXFAN2_REG, fanlevel);

                    CPU_Fan_Level = SYS_Fan_Level = AUX_Fan_Level = level;
                    break;

                default:
                    break;
            }
            Console.WriteLine("fanNum =  0x{0:x} , fanlevel =  0x{1:x}", fanNum, fanlevel);
        }


		public void Get_Temperature(ref uint?[] Temperature)
		{	
			//TemperatureRegisters = new ushort[] { 0x27 };
			for (int i = 0; i < TemperatureRegisters.Length; i++)
            {
				byte data_tmp = ReadByte(TemperatureRegisters[i]); // controller temperature
                Temperature[i] = data_tmp;
            }
		}

        public void Get_LPCIO_CPU_Temperature(ref uint?[] Temperature)
        {
            ushort[] CPU_register = new ushort[] { 0x4F4 };
            
            //TemperatureRegisters = new ushort[] { 0x27 };
            for (int i = 0; i < TemperatureRegisters.Length; i++)
            {
                byte data_tmp = ReadByte(CPU_register[i]); // controller temperature
                Temperature[i] = data_tmp;
            }
        }

        private enum VoltageType
        {
            VOLTAGE_TYPE_1V,
            VOLTAGE_TYPE_3_3V,
            VOLTAGE_TYPE_5V,
            VOLTAGE_TYPE_12V
        }

		public void Get_Voltage(ref uint?[] voltages)
		{

			voltageTypes = new VoltageType[] { VoltageType.VOLTAGE_TYPE_1V, VoltageType.VOLTAGE_TYPE_5V, VoltageType.VOLTAGE_TYPE_12V, VoltageType.VOLTAGE_TYPE_3_3V };
            for (int i = 0; i < voltages.Length; i++)
            {
                byte data = ReadByte(voltageRegisters[i]);
                int Temp = 0;
                switch (LPCIO_ID)
                {
                    case 0xD121:
                            switch (voltageTypes[i])
                            {
                                case VoltageType.VOLTAGE_TYPE_1V:
                                    Temp = data * 8;
                                    break;
                                case VoltageType.VOLTAGE_TYPE_5V:
                                    Temp = data * 8 * (20 + 10) / 10;
                                    break;
                                case VoltageType.VOLTAGE_TYPE_12V:
                                    Temp = data * 8 * (56 + 10) / 10;
                                    break;
                                case VoltageType.VOLTAGE_TYPE_3_3V:
                                    Temp = data * 8 * (34 + 34) / 34;
                                    break;
                            }
                        voltages[i] = Convert.ToUInt32(((Temp / 1000) << 4) + ((Temp / 100) % 10));
                        break;

                    case 0xC803:
                        switch (voltageTypes[i])
                        {
                            case VoltageType.VOLTAGE_TYPE_1V:
                                Temp = data * 2;
                                break;
                            case VoltageType.VOLTAGE_TYPE_5V:
                                Temp = data * 3;
                                break;
                            case VoltageType.VOLTAGE_TYPE_12V:
                                Temp = data * 12;
                                break;
                            case VoltageType.VOLTAGE_TYPE_3_3V:
                                Temp = data * 2;
                                break;
                        }
                        voltages[i] = Convert.ToUInt32(((Temp << 3) / 1000 << 4) + ((Temp << 3) / 100 % 10));
                        break;
                }

				
            }
            //return ref voltages;
        }

        public int GetChipID()
        {	
           	int all;
           	WinbondNuvotonFintekEnter();
           	byte id = ReadREGByte(NCT5567_Constants.CHIP_ID_REGISTER);
      		byte revision = ReadREGByte(NCT5567_Constants.CHIP_REVISION_REGISTER);
			all = ((id<<8)|revision);
            Nct6XXX_exit();   
            return all;
		}

        private void Nct6XXX_LDN_select(uint bank)
        {

            Ring0.WriteIoPort(registerPort, NCT5567_Constants.NCT5567_DEV);
            Ring0.WriteIoPort(valuePort, Convert.ToByte(bank));

            return;
        }

        public byte ReadREGByte(byte register)
        {
     	 	Ring0.WriteIoPort(registerPort, register);
            return Ring0.ReadIoPort(valuePort);
   		}

	
		/*private bool IsNuvotonVendor()
		{
			return ((ReadByte(VENDOR_ID_HIGH_REGISTER) << 8) |
		  ReadByte(VENDOR_ID_LOW_REGISTER)) == NUVOTON_VENDOR_ID;
		}*/


		private byte ReadByte(ushort address)
		{
			byte bank = (byte)(address >> 8);
			byte register = (byte)(address & 0xFF);
			Ring0.WriteIoPort(port + ADDRESS_REGISTER_OFFSET, BANK_SELECT_REGISTER);
			Ring0.WriteIoPort(port + DATA_REGISTER_OFFSET, bank);
			Ring0.WriteIoPort(port + ADDRESS_REGISTER_OFFSET, register);
			return Ring0.ReadIoPort(port + DATA_REGISTER_OFFSET);
		}


        public uint Readword(uint reg)
        {
            uint val = 0;
            uint bitstr = 0;
            Ring0.WriteIoPort(registerPort, Convert.ToByte(reg++));
            bitstr = Ring0.ReadIoPort(valuePort);
            val = bitstr << 8;

            Ring0.WriteIoPort(registerPort, Convert.ToByte(reg));
            bitstr = Ring0.ReadIoPort(valuePort);
            val |= bitstr;

            return val;
        }

        public void WriteByte(uint address,uint data)
        {
            byte bank = (byte)(address >> 8);
            byte register = (byte)(address & 0xFF);
            Ring0.WriteIoPort(port + ADDRESS_REGISTER_OFFSET, BANK_SELECT_REGISTER);
            Ring0.WriteIoPort(port + DATA_REGISTER_OFFSET, bank);
            Ring0.WriteIoPort(port + ADDRESS_REGISTER_OFFSET, register);
            Ring0.WriteIoPort(port + DATA_REGISTER_OFFSET, Convert.ToByte(data));
        }

        public void WinbondNuvotonFintekEnter()
		{
      		Ring0.WriteIoPort(registerPort, 0x87);
      		Ring0.WriteIoPort(registerPort, 0x87);
    	}

        public void Nct6XXX_exit()
        {

            Ring0.WriteIoPort(registerPort, 0xaa);
            
            return;
        }
    }
}

