namespace pLED_customizer
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.panel_led = new System.Windows.Forms.Panel();
            this.trackBar_Scale = new System.Windows.Forms.TrackBar();
            this.check_Blue = new System.Windows.Forms.CheckBox();
            this.check_Green = new System.Windows.Forms.CheckBox();
            this.check_Red = new System.Windows.Forms.CheckBox();
            this.button_data = new System.Windows.Forms.Button();
            this.button_Clear = new System.Windows.Forms.Button();
            this.serialPort_PIC = new System.IO.Ports.SerialPort(this.components);
            this.panel_led.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scale)).BeginInit();
            this.SuspendLayout();
            // 
            // panel_led
            // 
            this.panel_led.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.panel_led.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel_led.Controls.Add(this.trackBar_Scale);
            this.panel_led.Cursor = System.Windows.Forms.Cursors.Cross;
            this.panel_led.Location = new System.Drawing.Point(259, 12);
            this.panel_led.MinimumSize = new System.Drawing.Size(500, 500);
            this.panel_led.Name = "panel_led";
            this.panel_led.Size = new System.Drawing.Size(513, 513);
            this.panel_led.TabIndex = 0;
            this.panel_led.Paint += new System.Windows.Forms.PaintEventHandler(this.panel_led_Paint);
            this.panel_led.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_led_MouseDown);
            this.panel_led.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel_led_MouseMove);
            // 
            // trackBar_Scale
            // 
            this.trackBar_Scale.BackColor = System.Drawing.SystemColors.ControlDark;
            this.trackBar_Scale.Cursor = System.Windows.Forms.Cursors.Default;
            this.trackBar_Scale.LargeChange = 1;
            this.trackBar_Scale.Location = new System.Drawing.Point(4, 14);
            this.trackBar_Scale.Maximum = 4;
            this.trackBar_Scale.Name = "trackBar_Scale";
            this.trackBar_Scale.Size = new System.Drawing.Size(104, 45);
            this.trackBar_Scale.TabIndex = 0;
            this.trackBar_Scale.ValueChanged += new System.EventHandler(this.trackBar_Scale_ValueChanged);
            // 
            // check_Blue
            // 
            this.check_Blue.BackgroundImage = global::pLED_customizer.Properties.Resources.blue;
            this.check_Blue.Location = new System.Drawing.Point(193, 452);
            this.check_Blue.Name = "check_Blue";
            this.check_Blue.Size = new System.Drawing.Size(60, 17);
            this.check_Blue.TabIndex = 3;
            this.check_Blue.Text = "Blue";
            this.check_Blue.UseVisualStyleBackColor = true;
            // 
            // check_Green
            // 
            this.check_Green.BackgroundImage = global::pLED_customizer.Properties.Resources.green;
            this.check_Green.Location = new System.Drawing.Point(193, 429);
            this.check_Green.Name = "check_Green";
            this.check_Green.Size = new System.Drawing.Size(60, 17);
            this.check_Green.TabIndex = 2;
            this.check_Green.Text = "Green";
            this.check_Green.UseVisualStyleBackColor = true;
            // 
            // check_Red
            // 
            this.check_Red.BackgroundImage = global::pLED_customizer.Properties.Resources.red;
            this.check_Red.Location = new System.Drawing.Point(193, 406);
            this.check_Red.Name = "check_Red";
            this.check_Red.Size = new System.Drawing.Size(60, 17);
            this.check_Red.TabIndex = 1;
            this.check_Red.Text = "Red";
            this.check_Red.UseVisualStyleBackColor = true;
            // 
            // button_data
            // 
            this.button_data.Location = new System.Drawing.Point(178, 487);
            this.button_data.Name = "button_data";
            this.button_data.Size = new System.Drawing.Size(75, 23);
            this.button_data.TabIndex = 4;
            this.button_data.Text = "Get Data";
            this.button_data.UseVisualStyleBackColor = true;
            this.button_data.Click += new System.EventHandler(this.button_data_Click);
            // 
            // button_Clear
            // 
            this.button_Clear.Location = new System.Drawing.Point(97, 487);
            this.button_Clear.Name = "button_Clear";
            this.button_Clear.Size = new System.Drawing.Size(75, 23);
            this.button_Clear.TabIndex = 5;
            this.button_Clear.Text = "Clear";
            this.button_Clear.UseVisualStyleBackColor = true;
            this.button_Clear.Click += new System.EventHandler(this.button_Clear_Click);
            // 
            // serialPort_PIC
            // 
            this.serialPort_PIC.BaudRate = 19200;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(784, 522);
            this.Controls.Add(this.button_Clear);
            this.Controls.Add(this.button_data);
            this.Controls.Add(this.check_Blue);
            this.Controls.Add(this.check_Green);
            this.Controls.Add(this.check_Red);
            this.Controls.Add(this.panel_led);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(800, 560);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "pLED-2014";
            this.SizeChanged += new System.EventHandler(this.MainForm_SizeChanged);
            this.panel_led.ResumeLayout(false);
            this.panel_led.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scale)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_led;
        private System.Windows.Forms.CheckBox check_Red;
        private System.Windows.Forms.CheckBox check_Green;
        private System.Windows.Forms.CheckBox check_Blue;
        private System.Windows.Forms.Button button_data;
        private System.Windows.Forms.Button button_Clear;
        private System.Windows.Forms.TrackBar trackBar_Scale;
        private System.IO.Ports.SerialPort serialPort_PIC;
    }
}

