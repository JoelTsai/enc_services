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

    static class NCT6776_Constants
    {

        internal const uint NCT6XXX_ENV_CTRL_FAN_SEN_CPUTIN = 0;
        internal const uint NCT6XXX_ENV_CTRL_FAN_SEN_SYSTIN = 1;
        internal const uint NCT6XXX_ENV_CTRL_FAN_SEN_AUXTIN = 2;
        internal const uint NCT6XXX_ENV_CTRL_FAN_ALL = 0xFF;

        internal const uint Nct6776_ENV_FAN_CONFIG_SYSFAN_REG = 0x004;
        internal const uint Nct6776_ENV_FAN_CONFIG_FAN_PWM = 0x000;
        internal const uint Nct6776_ENV_FAN_MODE_SYSFAN_REG = 0x102;
        internal const uint Nct6776_ENV_FAN_MODE_CPUFAN_REG = 0x202;
        internal const uint Nct6776_ENV_FAN_MODE_AUXFAN_REG = 0x302;
        internal const uint Nct6776_ENV_FAN_MODE_FAN_MANUAL_MODE = 0x000;
        internal const ushort Nct6776_ENV_FAN_SET_SYSFAN_REG = 0x109;
        internal const ushort Nct6776_ENV_FAN_SET_CPUFAN_REG = 0x209;
        internal const ushort Nct6776_ENV_FAN_SET_AUXFAN_REG = 0x309;
        internal const ushort Nct6776_ENV_FAN_GET_SYSFAN_VAL_H_REG = 0x656;
        internal const ushort Nct6776_ENV_FAN_GET_SYSFAN_VAL_L_REG = 0x657;
        internal const ushort Nct6776_ENV_FAN_GET_CPUFAN_VAL_H_REG = 0x658;
        internal const ushort Nct6776_ENV_FAN_GET_CPUFAN_VAL_L_REG = 0x659;
        internal const ushort Nct6776_ENV_FAN_GET_AUXFAN_VAL_H_REG = 0x65A;
        internal const ushort Nct6776_ENV_FAN_GET_AUXFAN_VAL_L_REG = 0x65B;
        internal const ushort Nct6776_ENV_FAN_GET_SYSFAN_COUNT_H_REG = 0x630;
        internal const ushort Nct6776_ENV_FAN_GET_SYSFAN_COUNT_L_REG = 0x631;
        internal const ushort Nct6776_ENV_FAN_GET_CPUFAN_COUNT_H_REG = 0x632;
        internal const ushort Nct6776_ENV_FAN_GET_CPUFAN_COUNT_L_REG = 0x633;
        internal const ushort Nct6776_ENV_FAN_GET_AUXFAN_COUNT_H_REG = 0x634;
        internal const ushort Nct6776_ENV_FAN_GET_AUXFAN_COUNT_L_REG = 0x635;

        internal const uint Nct6776_ENV_VOLT_CONFIG_VBAT_ENABLE = 0x01;
        internal const uint Nct6776_ENV_VOLT_CONFIG_VBAT_REG = 0x05D;
        internal const uint Nct6776_ENV_VOLT_CPUCORE_REG = 0x020;
        internal const uint Nct6776_ENV_VOLT_12V_REG = 0x021;
        internal const uint Nct6776_ENV_VOLT_AVCC_REG = 0x022;
        internal const uint Nct6776_ENV_VOLT_3VCC_REG = 0x023;
        internal const uint Nct6776_ENV_VOLT_VIN1_REG = 0x024;
        internal const uint Nct6776_ENV_VOLT_5V_REG = 0x025;
        internal const uint Nct6776_ENV_VOLT_VIN3_REG = 0x026;
        internal const uint Nct6776_ENV_VOLT_3VSB_REG = 0x550;
        internal const uint Nct6776_ENV_VOLT_VBAT_REG = 0x551;

        internal const byte NCT6XXX_DEV = 0x07;

        internal const uint NCT6XXX_PARALLEL_PORT_LDN = 0x01;
        internal const uint NCT6XXX_UART_A_LDN = 0x02;
        internal const uint NCT6XXX_UART_B_LDN = 0x03;
        internal const uint NCT6XXX_GPIO_LDN = 0x07;
        internal const uint NCT6XXX_PME_LDN = 0x04;
        internal const uint NCT6XXX_HW_MONITOR_LDN = 0x0B;
        internal const uint NCT6XXX_GPIO_WDT1_LDN = 0x08;
        internal const uint NCT6XXX_PARALLEL_VID_LDN = 0x0D;

        internal const uint NCT6XXX_ENV_CTRL_BASE_ADDR_REG = 0x60;

        internal static readonly uint[] FAN_Level = { 0x12, 0x18, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 0xD2, 0xF0, 0xFF };


        internal const byte CHIP_ID_REGISTER = 0x20;
        internal const byte CHIP_REVISION_REGISTER = 0x21;
        internal const byte BASE_ADDRESS_REGISTER = 0x60;
    }
    public class NCT677X 
    {
    	private uint port;
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

        public static uint CPU_Fan_Level = 0;
        public static uint SYS_Fan_Level = 0;
        public static uint AUX_Fan_Level = 0;

        private static readonly uint FAN_offset = 0x03;//this offset is the level different of SYS_FAN and CPU_FAN

        private static bool FAN_install_flag=false;
        //fasle for normal true for non-install;

        public NCT677X()
      	{	

            //Ring0.Open();
            NCT_init();

            // Control Fan in Manual Mode
            WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_MODE_SYSFAN_REG, NCT6776_Constants.Nct6776_ENV_FAN_MODE_FAN_MANUAL_MODE);
            WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_MODE_CPUFAN_REG, NCT6776_Constants.Nct6776_ENV_FAN_MODE_FAN_MANUAL_MODE);
            WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_MODE_AUXFAN_REG, NCT6776_Constants.Nct6776_ENV_FAN_MODE_FAN_MANUAL_MODE);

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
            if(Enclsoure.Enclsoure_class.Model_ID != Enclsoure.Enclsoure_class.Model_VA8020)
            {
                FanRegisters = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_SET_CPUFAN_REG };
                FanRegisters_high = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_GET_CPUFAN_COUNT_H_REG };
                FanRegisters_low = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_GET_CPUFAN_COUNT_L_REG };
            }
            else
            {
                FanRegisters = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_SET_CPUFAN_REG, NCT6776_Constants.Nct6776_ENV_FAN_SET_SYSFAN_REG };
                FanRegisters_high = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_GET_CPUFAN_COUNT_H_REG, NCT6776_Constants.Nct6776_ENV_FAN_GET_SYSFAN_COUNT_H_REG };
                FanRegisters_low = new ushort[] { NCT6776_Constants.Nct6776_ENV_FAN_GET_CPUFAN_COUNT_L_REG, NCT6776_Constants.Nct6776_ENV_FAN_GET_SYSFAN_COUNT_L_REG };
            }
            SIO_FAN_NUM = Convert.ToUInt32(FanRegisters.Length);
        }

        private void NCT_init()
        {
            WinbondNuvotonFintekEnter();
            Nct6XXX_LDN_select(NCT6776_Constants.NCT6XXX_HW_MONITOR_LDN);
            port = Readword(NCT6776_Constants.NCT6XXX_ENV_CTRL_BASE_ADDR_REG);
            Nct6XXX_exit();

        }
        public void Get_Fan(ref uint?[] Fan)
		{
			
			int fans = 0;
			int fanCount = 0;
			for (int i = 0; i < FanRegisters.Length; i++)
            {
				int Fan_Level = ReadByte(FanRegisters[i]);
				byte Speed_high = ReadByte(FanRegisters_high[i]); // CPU fan Speed
				byte Speed_low = ReadByte(FanRegisters_low[i]);
				byte data_tmp = ReadByte(FanRegisters[i]); // controller temperature
				int FanSpeed=0;

				if (( Speed_high== 0xFF) && (Speed_low == 0x1F))
				{
					fans = 0;
                    if (FAN_install_flag == false)
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_NOT_INSTALLED,
                                              Convert.ToUInt16(i));
                        FAN_install_flag = true;
                    }
                }
				else
				{
					fanCount = (Speed_high << 5) + (Speed_low & 0x1F);
					FanSpeed = fanCount >> 4;
					fans = (Fan_Level << 16) | (FanSpeed);
                    if (FAN_install_flag == true)
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_FUNCTIONAL,
                                              Convert.ToUInt16(i));
                        FAN_install_flag = false;
                    }

                }
				Fan[i] = Convert.ToUInt32(fans);
			}
            

		}

        public void Set_Fan(uint fanNum, uint level)
        {
            uint fanlevel = 0;
           // Console.WriteLine("fanNum =  0x{0:x}", fanNum);
            switch (fanNum)
            {
                case NCT6776_Constants.NCT6XXX_ENV_CTRL_FAN_SEN_CPUTIN:
                    level += FAN_offset;//offset
                    level= (level > 15) ?  15 : level;
                    fanlevel = NCT6776_Constants.FAN_Level[level];
                    //fanlevel = level;
                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_CPUFAN_REG, fanlevel);
                    CPU_Fan_Level = level;
                    break;

                case NCT6776_Constants.NCT6XXX_ENV_CTRL_FAN_SEN_SYSTIN:
                    fanlevel = NCT6776_Constants.FAN_Level[level];
                    //fanlevel = level;
                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_SYSFAN_REG, fanlevel);
                    SYS_Fan_Level = level;
                    break;

                case NCT6776_Constants.NCT6XXX_ENV_CTRL_FAN_SEN_AUXTIN:
                    fanlevel = NCT6776_Constants.FAN_Level[level];
                   // fanlevel = level;
                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_AUXFAN_REG, fanlevel);
                    AUX_Fan_Level = level;
                    break;

                case NCT6776_Constants.NCT6XXX_ENV_CTRL_FAN_ALL:
                    fanlevel = NCT6776_Constants.FAN_Level[level];
                    //fanlevel = level;
                    //CPU_Fan_Level = fanlevel;
                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_CPUFAN_REG, fanlevel);

                    //fanlevel = NCT6776_Constants.FAN_Level[level];

                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_SYSFAN_REG, fanlevel);
                    WriteByte(NCT6776_Constants.Nct6776_ENV_FAN_SET_AUXFAN_REG, fanlevel);

                    CPU_Fan_Level = SYS_Fan_Level = AUX_Fan_Level = level;
                    break;

                default:
                    break;
            }
            Console.WriteLine("fanNum =  0x{0:x} , fanlevel =  0x{1:x}", fanNum, fanlevel);
        }


		public void Get_Temperature(ref uint?[] Temperature)
		{	
			TemperatureRegisters = new ushort[] { 0x27 };
			for (int i = 0; i < TemperatureRegisters.Length; i++)
            {
				byte data_tmp = ReadByte(TemperatureRegisters[i]); // controller temperature
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
            // For 3120, JKPI 8100(3340), Sony 3340, Channel 3340
            // - 1V    => reg : 0x20
            // - 5V    => reg : 0x26
            // - 12V   => reg : 0x25
            // - 3.3V  => reg : 0x23
			voltageRegisters = new ushort[] { 0x020, 0x026, 0x025, 0x023 };
			voltageTypes = new VoltageType[] { VoltageType.VOLTAGE_TYPE_1V, VoltageType.VOLTAGE_TYPE_5V, VoltageType.VOLTAGE_TYPE_12V, VoltageType.VOLTAGE_TYPE_3_3V };
            for (int i = 0; i < voltages.Length; i++)
            {
                byte data = ReadByte(voltageRegisters[i]);
                int Temp = 0;
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
				
            }
            //return ref voltages;
        }

        public int GetChipID()
        {	
           	int all;
           	WinbondNuvotonFintekEnter();
           	byte id = ReadREGByte(NCT6776_Constants.CHIP_ID_REGISTER);
      		byte revision = ReadREGByte(NCT6776_Constants.CHIP_REVISION_REGISTER);
			all = ((id<<8)|revision);
            Nct6XXX_exit();   
            return all;
		}

        private void Nct6XXX_LDN_select(uint bank)
        {

            Ring0.WriteIoPort(registerPort, NCT6776_Constants.NCT6XXX_DEV);
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

