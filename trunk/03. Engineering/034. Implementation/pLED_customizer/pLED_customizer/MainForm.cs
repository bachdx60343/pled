using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace pLED_customizer
{
    public partial class MainForm : Form
    {
        private static Size led_size;
        private static int pad;
        private static int hole;
        private static int led_count;
        private static int resol;
        private static Single angle;
        private static Rectangle[,] rect_led;
        private static Graphics g;
        private static Pen pen_black;
        private static Brush br_red, br_green, br_blue, br_black, br_clear;
        private static Brush br_rg, br_gb, br_rb, br_rgb;
        private static System.Collections.BitArray led_bits;
        private DataForm dtForm;
        private static float scale;
        private static byte[] rs232_data;
        private delegate void data_Receive_Handler(String tx);
        private static int rx_status;

        private void Initialize_panel_led()
        {
            led_size = new System.Drawing.Size(10, 10);
            pad = 5;
            hole = 10;
            led_count = 16;
            resol = 60;
            angle = 360 / resol;
            rect_led = new Rectangle[resol, led_count];

            g = this.panel_led.CreateGraphics();
            pen_black = new Pen(Color.Black, 1);
            br_red = new SolidBrush(Color.Red);
            br_green = new SolidBrush(Color.Green);
            br_blue = new SolidBrush(Color.Blue);
            br_black = new SolidBrush(Color.Black);
            br_clear = new SolidBrush(System.Drawing.Color.FromName(System.Drawing.SystemColors.ControlDarkDark.Name));

            led_bits = new System.Collections.BitArray(led_count * 3 * resol);
            //led_bits.SetAll(true);

            br_rg = new SolidBrush(Color.Orange);
            br_gb = new SolidBrush(Color.Cyan);
            br_rb = new SolidBrush(Color.Violet);
            br_rgb = new SolidBrush(Color.White);

            scale = 1.0F;

            dtForm = new DataForm();
            rs232_data = new Byte[11];

            rs232_data[0] = 83;
            rs232_data[1] = 84;
            rs232_data[9] = 69;
            rs232_data[10] = 68;

            rs232_data[2] = 13;
            rs232_data[3] = 4;
            rs232_data[4] = 14;
            rs232_data[5] = 1;
            rs232_data[6] = 19;
            rs232_data[7] = 52;
            rs232_data[8] = 29;

            rx_status = 0;
        }

        private Brush getBrush(int resPos, int ledPos)
        {
            System.Collections.BitArray bite = new System.Collections.BitArray(8);
            byte[] bitref = new byte[1];
            Brush br;

            bite.Set(0, led_bits.Get(48 * resPos + 3 * ledPos));
            bite.Set(1, led_bits.Get(48 * resPos + 3 * ledPos + 1));
            bite.Set(2, led_bits.Get(48 * resPos + 3 * ledPos + 2));
            bite.CopyTo(bitref, 0);
            switch (bitref[0])
            {
                case 1:
                    br = br_blue;
                    break;
                case 2:
                    br = br_red;
                    break;
                case 3:
                    br = br_rb;
                    break;
                case 4:
                    br = br_green;
                    break;
                case 5:
                    br = br_gb;
                    break;
                case 6:
                    br = br_rg;
                    break;
                case 7:
                    br = br_rgb;
                    break;
                default:
                    br = br_black;
                    break;
            }
            return br;
        }

        public MainForm()
        {
            InitializeComponent();
            Initialize_panel_led();
        }

        private void panel_led_Paint(object sender, PaintEventArgs e)
        {
            Point center = new Point(this.panel_led.Size.Width / 2, this.panel_led.Size.Height / 2);
            Matrix transMatrix = new Matrix();
            Point[] transPoint = new Point[led_count];
            Point[] rotatPoint = new Point[led_count];

            g = this.panel_led.CreateGraphics();
            g.Clear(System.Drawing.Color.FromName(System.Drawing.SystemColors.ControlDarkDark.Name));

            g.TranslateTransform(center.X, center.Y);
            g.DrawLine(pen_black, 0, -center.Y, 0, center.Y);
            g.DrawLine(pen_black, -center.X, 0, center.X, 0);
            g.ResetTransform();

            for (int i = 0; i < led_count; i++)
            {
                transPoint[i].X = 0;
                transPoint[i].Y = (int)(-hole - (led_size.Height * (i + 0.5)) - pad * i);
            }

            transMatrix.Translate(center.X, center.Y);
            transMatrix.Scale(0, scale);
            transMatrix.TransformPoints(transPoint);
            Size tSize = new Size();
            tSize.Width = (int)(led_size.Width + scale / 2);
            tSize.Height = (int)(led_size.Height + scale / 2);
            for (int i = 0; i < led_count; i++)
            {
                rect_led[0, i].X = transPoint[i].X - tSize.Width / 2;
                rect_led[0, i].Y = transPoint[i].Y - tSize.Height / 2;
                rect_led[0, i].Size = tSize;
            }
            transMatrix.Reset();

            for (int i = 1; i < resol; i++)
            {
                for (int j = 0; j < led_count; j++)
                {
                    rotatPoint[j] = transPoint[j];
                }
                transMatrix.RotateAt(angle, center);
                transMatrix.TransformPoints(rotatPoint);
                for (int j = 0; j < led_count; j++)
                {
                    rect_led[i, j].X = rotatPoint[j].X - tSize.Width / 2;
                    rect_led[i, j].Y = rotatPoint[j].Y - tSize.Height / 2;
                    rect_led[i, j].Size = tSize;
                }
            }

            int count = 0;
            foreach (Rectangle rec in rect_led)
            {
                g.FillEllipse(getBrush((int)(count / led_count), count % led_count), rec);
                count++;
            }
            //g.Dispose();
        }

        private void MainForm_SizeChanged(object sender, EventArgs e)
        {
            Size sz = new Size();
            sz.Height = this.Size.Height * 500 / 560;
            sz.Width = sz.Height;
            this.panel_led.Size = sz;
            Point pt = new Point();
            pt.X = this.Size.Width - sz.Width - 28;
            pt.Y = this.panel_led.Location.Y;
            this.panel_led.Location = pt;

            led_size.Height = sz.Height / 50;
            led_size.Width = sz.Width / 50;
            pad = sz.Height / 100;
            //hole = sz.Height * 6 / 500;
        }

        private void button_data_Click(object sender, EventArgs e)
        {
            if(!dtForm.Visible)
            {
                dtForm.Bitsfield = led_bits;
                dtForm.Led_count = led_count;
                dtForm.Resol = resol;
                dtForm.Show(this.FindForm());
            }
        }

        private void panel_led_MouseMove(object sender, MouseEventArgs e)
        {
            int count = 0;

            foreach (Rectangle rt in rect_led)
            {
                if (rt.Contains(e.Location))
                {
                    if (e.Button == System.Windows.Forms.MouseButtons.Left)
                    {
                        if (this.check_Blue.Checked)
                        {
                            led_bits.Set(count * 3, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3, false);
                        }
                        if (this.check_Red.Checked)
                        {
                            led_bits.Set(count * 3 + 1, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3 + 1, false);
                        }
                        if (this.check_Green.Checked)
                        {
                            led_bits.Set(count * 3 + 2, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3 + 2, false);
                        }
                        g.FillEllipse(getBrush((int)(count / led_count), count % led_count), rt);
                    }
                    else if (e.Button == System.Windows.Forms.MouseButtons.Right)
                    {
                        led_bits.Set(count * 3, false);
                        led_bits.Set(count * 3 + 1, false);
                        led_bits.Set(count * 3 + 2, false);
                        g.FillEllipse(getBrush((int)(count / led_count), count % led_count), rt);
                    }
                }
                count += 1;
            }
        }

        private void panel_led_MouseDown(object sender, MouseEventArgs e)
        {
            int count = 0;

            foreach (Rectangle rt in rect_led)
            {
                if (rt.Contains(e.Location))
                {
                    if (e.Button == System.Windows.Forms.MouseButtons.Left)
                    {
                        if (this.check_Blue.Checked)
                        {
                            led_bits.Set(count * 3, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3, false);
                        }
                        if (this.check_Red.Checked)
                        {
                            led_bits.Set(count * 3 + 1, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3 + 1, false);
                        }
                        if (this.check_Green.Checked)
                        {
                            led_bits.Set(count * 3 + 2, true);
                        }
                        else
                        {
                            led_bits.Set(count * 3 + 2, false);
                        }
                        g.FillEllipse(getBrush((int)(count / led_count), count % led_count), rt);
                    }
                    else if (e.Button == System.Windows.Forms.MouseButtons.Right)
                    {
                        led_bits.Set(count * 3, false);
                        led_bits.Set(count * 3 + 1, false);
                        led_bits.Set(count * 3 + 2, false);
                        g.FillEllipse(getBrush((int)(count / led_count), count % led_count), rt);
                    }
                }
                count += 1;
            }
        }

        private void button_Clear_Click(object sender, EventArgs e)
        {
            led_bits.SetAll(false);
            this.panel_led.Refresh();
        }

        private void trackBar_Scale_ValueChanged(object sender, EventArgs e)
        {
            scale = (float)Math.Pow(2, this.trackBar_Scale.Value);
            this.panel_led.Refresh();
        }

        private void button_Connect_Click(object sender, EventArgs e)
        {
            if (this.serialPort_PIC.IsOpen)
            {
                this.serialPort_PIC.Close();
            }
            if (this.comboBox_COM.SelectedItem != null)
            {
                this.serialPort_PIC.PortName = this.comboBox_COM.SelectedItem.ToString();
                //this.serialPort_PIC.BaudRate = 19200;
                //this.serialPort_PIC.DataBits = 8;
                //this.serialPort_PIC.Parity = Parity.Even;
                //this.serialPort_PIC.StopBits = StopBits.One;
                //this.serialPort_PIC.Handshake = Handshake.None;
                try
                {
                    this.serialPort_PIC.Open();
                    label_COMstatus.Text = serialPort_PIC.PortName + " connected";
                }
                catch (Exception)
                {
                    MessageBox.Show("An error occured. Cannot open port.");
                    //throw;
                }
            }
            else
            {
                this.label_COMstatus.Text = "not connected";
            }
        }

        private void button_RunText_Click(object sender, EventArgs e)
        {
            if (this.serialPort_PIC.IsOpen && this.textBox_RunText.Text != "")
            {
                this.serialPort_PIC.Write(this.textBox_RunText.Text);
                this.textBox_RunText.Text = "";
            }
        }

        private void timer_sec_Tick(object sender, EventArgs e)
        {
            System.DateTime moment = System.DateTime.Now;
            this.textBox_Date.Text = moment.Day.ToString();
            this.textBox_Date.Text += "/" + moment.Month.ToString();
            this.textBox_Date.Text += "/" + moment.Year.ToString();
            this.textBox_Date.Text += "-" + moment.DayOfWeek.ToString();

            this.textBox_Time.Text = moment.Hour.ToString();
            this.textBox_Time.Text += ":" + moment.Minute.ToString();
            this.textBox_Time.Text += ":" + moment.Second.ToString();
        }

        private void button_Update_Click(object sender, EventArgs e)
        {
            if (this.serialPort_PIC.IsOpen)
            {
                System.DateTime moment = System.DateTime.Now;
                Byte[] temp = new Byte[4];

                temp = BitConverter.GetBytes(moment.Day);
                rs232_data[2] = temp[0];
                temp = BitConverter.GetBytes(moment.Month);
                rs232_data[3] = temp[0];
                temp = BitConverter.GetBytes(moment.Year - 2000);
                rs232_data[4] = temp[0];
                temp = BitConverter.GetBytes((Int32)moment.DayOfWeek + 1);
                rs232_data[5] = temp[0];
                temp = BitConverter.GetBytes(moment.Hour);
                rs232_data[6] = temp[0];
                temp = BitConverter.GetBytes(moment.Minute);
                rs232_data[7] = temp[0];
                temp = BitConverter.GetBytes(moment.Second);
                rs232_data[8] = temp[0];

                try
                {
                    this.serialPort_PIC.Write(rs232_data, 0, 11);
                    //MessageBox.Show("Date, time's data sent: " + moment.ToString());
                }
                catch (Exception)
                {
                    MessageBox.Show("An error occured. Cannot send data.");
                    //throw;
                }
            }
        }

        private void rs232_receive(String tx)
        {
            this.textBox_RunText.Text = tx;
            if (tx == "O")
            {
                rx_status = 1;
            }
            else if (tx == "K" && rx_status == 1)
            {
                rx_status = 2;
            }
            if (tx.Contains("OK"))
            {
                rx_status = 2;
            }
            if (rx_status == 2)
            {
                rx_status = 0;
                MessageBox.Show("Date, time updated successfully!");
            }
        }

        private void serialPort_PIC_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String tx = serialPort_PIC.ReadExisting();
            this.BeginInvoke(new data_Receive_Handler(rs232_receive), tx);
        }

        private void comboBox_COM_Click(object sender, EventArgs e)
        {
            this.comboBox_COM.Items.Clear();
            foreach (string s in SerialPort.GetPortNames())
            {
                this.comboBox_COM.Items.Add(s);
            }

            if (this.comboBox_COM.Items.Count > 0)
            {
                if (this.serialPort_PIC.IsOpen)
                {
                    this.comboBox_COM.SelectedItem = this.serialPort_PIC.PortName;
                }
                else
                {
                    this.comboBox_COM.SelectedIndex = 0;
                }
            }
        }

        private void button_Disconnect_Click(object sender, EventArgs e)
        {
            if (this.serialPort_PIC.IsOpen)
            {
                this.serialPort_PIC.Close();
                label_COMstatus.Text = "not connected";
            }
        }

        private void button_Save_Click(object sender, EventArgs e)
        {
            this.saveFileDialog.ShowDialog(this);
        }

        private void button_Load_Click(object sender, EventArgs e)
        {
            this.openFileDialog.ShowDialog(this);
        }

        private void saveFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            System.IO.Stream file = this.saveFileDialog.OpenFile();
            Byte[] temp = new Byte[(led_count * 3 / 8) * resol];
            led_bits.CopyTo(temp, 0);
            file.Write(temp, 0, temp.Length);
            file.Close();
        }

        private void openFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            System.IO.Stream file = this.openFileDialog.OpenFile();
            Byte[] temp = new Byte[(led_count * 3 / 8) * resol];
            file.Read(temp, 0, temp.Length);
            file.Close();
            led_bits = new System.Collections.BitArray(temp);
            this.panel_led.Refresh();
        }
    }
}