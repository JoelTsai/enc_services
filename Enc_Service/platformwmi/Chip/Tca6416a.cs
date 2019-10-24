/*---------------------------------------------------------------------------**
**          Filename    : Tca6416a.cs                                        **
**          Description :Contorl Tca6416a chip                               **
**          Created on  :2019/07/15                                          **
**          Created by  : Cheng-Chieh Lai                                    **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using System.Threading;
using System.Globalization;
using System.Text;
using Enc_Service.platformwmi;



namespace Chip.Contrl
{
    static class TCA6416_Constants
    {
        public const uint BLEN = 1;
        public const uint WLEN = 2;
        public const uint DWLEN = 4;

        public const uint TCA6416A_I2C_ADDR_LO = 0x20;
		public const uint TCA6416A_I2C_ADDR_HI = 0x21;

		public const uint TCA6416A_PORT_0 	= 0;
		public const uint TCA6416A_PORT_1 	= 1;

		public const uint TCA6416A_GPIO_IN 	= 1;
		public const uint TCA6416A_GPIO_OUT = 0;
        public const uint TCA6416A_OUTPUT_PORT_0 =0x2;
        public const uint TCA6416A_OUTPUT_PORT_1 =0x3;

        public const uint ENC_LED_HDD_0         = 0;
		public const uint ENC_LED_HDD_1         = 1;
		public const uint ENC_LED_HDD_2         = 2;
		public const uint ENC_LED_HDD_3         = 3;
		public const uint ENC_LED_HDD_4         = 4;
		public const uint ENC_LED_HDD_5         = 5;
		public const uint ENC_LED_HDD_6         = 6;
		public const uint ENC_LED_HDD_7         = 7;
		public const uint ENC_LED_HDD_8         = 8;
		public const uint ENC_LED_HDD_9         = 9;
		public const uint ENC_LED_HDD_10        = 10;
		public const uint ENC_LED_HDD_11        = 11;
		public const uint ENC_LED_HDD_12        = 12;
		public const uint ENC_LED_HDD_13        = 13;
		public const uint ENC_LED_HDD_14        = 14;
		public const uint ENC_LED_HDD_15        = 15;
		public const uint ENC_LED_HDD           = 16;
		public const uint ENC_LED_POWER         = 17;
		public const uint ENC_LED_OPAS          = 18;
		public const uint ENC_LED_GLOBE_ERR     = 19;
		public const uint ENC_LED_RAID          = 20;
		public const uint ENC_LED_RECORD        = 21;
		public const uint ENC_LED_FAN           = 22;
		public const uint ENC_LED_BATTERY       = 23;
		public const uint ENC_LED_DEBUG         = 24;
		public const uint ENC_LED_PSU           = 25;
		public const uint ENC_LED_ETH1          = 26;
		public const uint ENC_LED_ETH2          = 27;

		public static ushort[] LedRegisters = new ushort[] { 0x20 ,0x21 };

	}//end of Constants
	
	public class TCA6416
	{
		//public PCHSMBUS SMB;
		public TCA6416()
		{
			//this.SMB = new PCHSMBUS();
		}

		public int Tca6416a_write_value(uint addr, uint reg, ref uint data)
		{
			// return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
			uint[] data_temp = { data };
			return PCHSMBUS.WriteSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp);
		}

		public int Tca6416a_read_value(uint addr, uint reg, ref uint data)
		{

			//return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
			int ret;
			uint[] data_temp = { data };
			ret = PCHSMBUS.ReadSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp);
			data = data_temp[0];
			return ret;

		}

		/*
		public void Tca6416a_get_led()
		{
			uint offset = 0;
			uint data, ldata, hdata;
			uint addr;
			uint fanCount;
		}
		*/	
		public void tca6416a_set_gpio_port_value (uint addr, uint port, ref uint data)
		{
			uint reg = 0;
			
			if (port == TCA6416_Constants.TCA6416A_PORT_0)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_0;
			}
			else if (port == TCA6416_Constants.TCA6416A_PORT_1)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_1;
			}
		
			Tca6416a_write_value (addr, reg,ref data);
		}

        public void tca6416a_get_gpio_port_value (uint addr, uint port, ref uint data)
        {
            uint reg = 0;

            if (port == TCA6416_Constants.TCA6416A_PORT_0)
            {
                reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_0;
            }
            else if (port == TCA6416_Constants.TCA6416A_PORT_1)
            {
                reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_1;
            }

            Tca6416a_read_value(addr, reg,ref data);
        }

		public void encSetLedStatus(uint chipId, uint port, uint PinId)
		{
			uint addr=0;
            switch(chipId)
			{
				case 0:
					addr=TCA6416_Constants.TCA6416A_I2C_ADDR_LO;
					break;
				case 1:
					addr=TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
					break;
			}
			
			
			Console.WriteLine("addr   =[{0:x}]", addr);
			Console.WriteLine("port   =[{0:x}]", port);
			Console.WriteLine("PinId  =[{0:x}]", PinId);
			tca6416a_set_gpio_port_value (addr, port, ref PinId);
			
			Console.WriteLine("encSetLedStatus End!");
		}

		public void encGetLedStatus(ref uint?[] Ledreg)
		{
			uint chipId=0;
			uint data_port_0=0;
			uint data_port_1=0;
			uint date_reg=0;
            uint PinId = 0;

            for (int i=0; i<TCA6416_Constants.LedRegisters.Length;i++)
			{
                chipId =TCA6416_Constants.LedRegisters[i];
				tca6416a_get_gpio_port_value (chipId, TCA6416_Constants.TCA6416A_PORT_0, ref PinId);
				data_port_0=PinId;
				tca6416a_get_gpio_port_value (chipId, TCA6416_Constants.TCA6416A_PORT_1, ref PinId);
				data_port_1=PinId;
				date_reg=(uint) (data_port_0 | (data_port_1<< 16));
				Ledreg[i] = date_reg;
				/*
				Console.WriteLine("chipId=[{0:x}]", chipId);
				Console.WriteLine("i=[{0:x}]", i);
				Console.WriteLine("PinId  =[{0:x}]", PinId);*/
				//Console.WriteLine("date_reg[{0}]=[{1:x}]", i,date_reg);
				
			}
			/*
			for (int i=0; i<TCA6416_Constants.LedRegisters.Length;i++)
			{
				Console.WriteLine("Ledreg  =[{0:x}]", Ledreg[i]);
			}
			*/
			//Console.WriteLine("encGetLedStatus End!");
		}
    }
}
