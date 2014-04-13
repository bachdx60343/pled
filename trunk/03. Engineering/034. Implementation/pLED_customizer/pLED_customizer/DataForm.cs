using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace pLED_customizer
{
    public partial class DataForm : Form
    {
        private System.Collections.BitArray bitsfield;
        private int led_count;
        private int resol;

        public System.Collections.BitArray Bitsfield
        {
            get { return bitsfield; }
            set { bitsfield = value; }
        }
        public int Led_count
        {
            get { return led_count; }
            set { led_count = value; }
        }
        public int Resol
        {
            get { return resol; }
            set { resol = value; }
        }

        public DataForm()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterParent;
        }

        private void button_hide_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button_update_Click(object sender, EventArgs e)
        {
            System.Collections.BitArray bl, re, gr;
            bl = new System.Collections.BitArray(bitsfield.Count / 3);
            re = new System.Collections.BitArray(bitsfield.Count / 3);
            gr = new System.Collections.BitArray(bitsfield.Count / 3);
            Byte[] b = new Byte[resol * led_count / 8];
            Byte[] r = new Byte[resol * led_count / 8];
            Byte[] g = new Byte[resol * led_count / 8];
            for (int i = 0; i < bitsfield.Count; i += 24)
            {
                for (int j = 0; j < 8; j++)
                {
                    bl.Set(i / 3 + j, bitsfield.Get(i + (7 - j) * 3));
                    re.Set(i / 3 + j, bitsfield.Get(i + (7 - j) * 3 + 1));
                    gr.Set(i / 3 + j, bitsfield.Get(i + (7 - j) * 3 + 2));
                }
            }
            bl.CopyTo(b, 0);
            re.CopyTo(r, 0);
            gr.CopyTo(g, 0);
            String Bdata = "";
            String Rdata = "";
            String Gdata = "";

            for (int i = 0; i < (resol * led_count / 8); i++)
            {
                Bdata += BitConverter.ToString(b, i, 1);
                Rdata += BitConverter.ToString(r, i, 1);
                Gdata += BitConverter.ToString(g, i, 1);
            }
            String txt = "";
            for (int i = 0; i < (resol * led_count / 4); i += (led_count / 4))
            {
                txt += "0x";
                txt += Bdata.Substring(i, (led_count / 4));
                txt += ", 0x";
                txt += Rdata.Substring(i, (led_count / 4));
                txt += ", 0x";
                txt += Gdata.Substring(i, (led_count / 4));
                txt += ",\r\n";
            }
            this.textBox_data.Text = txt;
        }

        private void DataForm_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible)
            {
                this.button_update_Click(sender, e);
            }
        }
    }
}
