using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace platformwmi
{
    class BigEndianBinaryWriter : BinaryWriter
    {
        public BigEndianBinaryWriter(System.IO.Stream steam)
            : base(steam)
        {
        }

        public override void Write(Int32 value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }

        public override void Write(UInt32 value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }

        public override void Write(short value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }

        public override void Write(ushort value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }

        public override void Write(Int64 value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }

        public override void Write(UInt64 value)
        {
            byte[] bs = BitConverter.GetBytes(value);
            Array.Reverse(bs);
            base.Write(bs);
        }
    }
}
