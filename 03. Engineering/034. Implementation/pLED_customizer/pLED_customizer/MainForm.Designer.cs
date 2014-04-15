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
            this.textBox_RunText = new System.Windows.Forms.TextBox();
            this.button_RunText = new System.Windows.Forms.Button();
            this.comboBox_COM = new System.Windows.Forms.ComboBox();
            this.button_Connect = new System.Windows.Forms.Button();
            this.textBox_Date = new System.Windows.Forms.TextBox();
            this.textBox_Time = new System.Windows.Forms.TextBox();
            this.button_Update = new System.Windows.Forms.Button();
            this.groupBox_Led = new System.Windows.Forms.GroupBox();
            this.button_Load = new System.Windows.Forms.Button();
            this.button_Save = new System.Windows.Forms.Button();
            this.groupBox_DateTime = new System.Windows.Forms.GroupBox();
            this.timer_sec = new System.Windows.Forms.Timer(this.components);
            this.groupBox_COM = new System.Windows.Forms.GroupBox();
            this.button_Disconnect = new System.Windows.Forms.Button();
            this.label_COMstatus = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.panel_led.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scale)).BeginInit();
            this.groupBox_Led.SuspendLayout();
            this.groupBox_DateTime.SuspendLayout();
            this.groupBox_COM.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel_led
            // 
            this.panel_led.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.panel_led.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel_led.Controls.Add(this.trackBar_Scale);
            this.panel_led.Cursor = System.Windows.Forms.Cursors.Cross;
            this.panel_led.Location = new System.Drawing.Point(268, 12);
            this.panel_led.MinimumSize = new System.Drawing.Size(500, 500);
            this.panel_led.Name = "panel_led";
            this.panel_led.Size = new System.Drawing.Size(500, 500);
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
            this.check_Blue.Location = new System.Drawing.Point(173, 83);
            this.check_Blue.Name = "check_Blue";
            this.check_Blue.Size = new System.Drawing.Size(60, 17);
            this.check_Blue.TabIndex = 3;
            this.check_Blue.Text = "Blue";
            this.check_Blue.UseVisualStyleBackColor = true;
            // 
            // check_Green
            // 
            this.check_Green.BackgroundImage = global::pLED_customizer.Properties.Resources.green;
            this.check_Green.Location = new System.Drawing.Point(173, 60);
            this.check_Green.Name = "check_Green";
            this.check_Green.Size = new System.Drawing.Size(60, 17);
            this.check_Green.TabIndex = 2;
            this.check_Green.Text = "Green";
            this.check_Green.UseVisualStyleBackColor = true;
            // 
            // check_Red
            // 
            this.check_Red.BackgroundImage = global::pLED_customizer.Properties.Resources.red;
            this.check_Red.Location = new System.Drawing.Point(173, 37);
            this.check_Red.Name = "check_Red";
            this.check_Red.Size = new System.Drawing.Size(60, 17);
            this.check_Red.TabIndex = 1;
            this.check_Red.Text = "Red";
            this.check_Red.UseVisualStyleBackColor = true;
            // 
            // button_data
            // 
            this.button_data.Location = new System.Drawing.Point(92, 77);
            this.button_data.Name = "button_data";
            this.button_data.Size = new System.Drawing.Size(75, 23);
            this.button_data.TabIndex = 4;
            this.button_data.Text = "Get Data";
            this.button_data.UseVisualStyleBackColor = true;
            this.button_data.Click += new System.EventHandler(this.button_data_Click);
            // 
            // button_Clear
            // 
            this.button_Clear.Location = new System.Drawing.Point(9, 77);
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
            this.serialPort_PIC.Parity = System.IO.Ports.Parity.Even;
            this.serialPort_PIC.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_PIC_DataReceived);
            // 
            // textBox_RunText
            // 
            this.textBox_RunText.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.textBox_RunText.Location = new System.Drawing.Point(6, 28);
            this.textBox_RunText.MaxLength = 10;
            this.textBox_RunText.Name = "textBox_RunText";
            this.textBox_RunText.Size = new System.Drawing.Size(100, 20);
            this.textBox_RunText.TabIndex = 6;
            // 
            // button_RunText
            // 
            this.button_RunText.Enabled = false;
            this.button_RunText.Location = new System.Drawing.Point(138, 28);
            this.button_RunText.Name = "button_RunText";
            this.button_RunText.Size = new System.Drawing.Size(75, 23);
            this.button_RunText.TabIndex = 7;
            this.button_RunText.Text = "Send Text";
            this.button_RunText.UseVisualStyleBackColor = true;
            this.button_RunText.Click += new System.EventHandler(this.button_RunText_Click);
            // 
            // comboBox_COM
            // 
            this.comboBox_COM.FormattingEnabled = true;
            this.comboBox_COM.Location = new System.Drawing.Point(6, 80);
            this.comboBox_COM.Name = "comboBox_COM";
            this.comboBox_COM.Size = new System.Drawing.Size(100, 21);
            this.comboBox_COM.TabIndex = 8;
            this.comboBox_COM.Click += new System.EventHandler(this.comboBox_COM_Click);
            // 
            // button_Connect
            // 
            this.button_Connect.Location = new System.Drawing.Point(138, 78);
            this.button_Connect.Name = "button_Connect";
            this.button_Connect.Size = new System.Drawing.Size(75, 23);
            this.button_Connect.TabIndex = 9;
            this.button_Connect.Text = "Connect";
            this.button_Connect.UseVisualStyleBackColor = true;
            this.button_Connect.Click += new System.EventHandler(this.button_Connect_Click);
            // 
            // textBox_Date
            // 
            this.textBox_Date.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.textBox_Date.Location = new System.Drawing.Point(6, 28);
            this.textBox_Date.Name = "textBox_Date";
            this.textBox_Date.ReadOnly = true;
            this.textBox_Date.Size = new System.Drawing.Size(112, 20);
            this.textBox_Date.TabIndex = 10;
            // 
            // textBox_Time
            // 
            this.textBox_Time.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.textBox_Time.Location = new System.Drawing.Point(6, 74);
            this.textBox_Time.Name = "textBox_Time";
            this.textBox_Time.ReadOnly = true;
            this.textBox_Time.Size = new System.Drawing.Size(112, 20);
            this.textBox_Time.TabIndex = 11;
            // 
            // button_Update
            // 
            this.button_Update.Location = new System.Drawing.Point(138, 49);
            this.button_Update.Name = "button_Update";
            this.button_Update.Size = new System.Drawing.Size(75, 23);
            this.button_Update.TabIndex = 12;
            this.button_Update.Text = "Update";
            this.button_Update.UseVisualStyleBackColor = true;
            this.button_Update.Click += new System.EventHandler(this.button_Update_Click);
            // 
            // groupBox_Led
            // 
            this.groupBox_Led.Controls.Add(this.button_Load);
            this.groupBox_Led.Controls.Add(this.button_Save);
            this.groupBox_Led.Controls.Add(this.check_Blue);
            this.groupBox_Led.Controls.Add(this.check_Red);
            this.groupBox_Led.Controls.Add(this.check_Green);
            this.groupBox_Led.Controls.Add(this.button_data);
            this.groupBox_Led.Controls.Add(this.button_Clear);
            this.groupBox_Led.Location = new System.Drawing.Point(12, 397);
            this.groupBox_Led.Name = "groupBox_Led";
            this.groupBox_Led.Size = new System.Drawing.Size(241, 113);
            this.groupBox_Led.TabIndex = 13;
            this.groupBox_Led.TabStop = false;
            this.groupBox_Led.Text = "Led Data";
            // 
            // button_Load
            // 
            this.button_Load.Location = new System.Drawing.Point(92, 37);
            this.button_Load.Name = "button_Load";
            this.button_Load.Size = new System.Drawing.Size(75, 23);
            this.button_Load.TabIndex = 7;
            this.button_Load.Text = "Load";
            this.button_Load.UseVisualStyleBackColor = true;
            this.button_Load.Click += new System.EventHandler(this.button_Load_Click);
            // 
            // button_Save
            // 
            this.button_Save.Location = new System.Drawing.Point(9, 37);
            this.button_Save.Name = "button_Save";
            this.button_Save.Size = new System.Drawing.Size(75, 23);
            this.button_Save.TabIndex = 6;
            this.button_Save.Text = "Save";
            this.button_Save.UseVisualStyleBackColor = true;
            this.button_Save.Click += new System.EventHandler(this.button_Save_Click);
            // 
            // groupBox_DateTime
            // 
            this.groupBox_DateTime.Controls.Add(this.textBox_Date);
            this.groupBox_DateTime.Controls.Add(this.textBox_Time);
            this.groupBox_DateTime.Controls.Add(this.button_Update);
            this.groupBox_DateTime.Location = new System.Drawing.Point(12, 182);
            this.groupBox_DateTime.Name = "groupBox_DateTime";
            this.groupBox_DateTime.Size = new System.Drawing.Size(241, 107);
            this.groupBox_DateTime.TabIndex = 14;
            this.groupBox_DateTime.TabStop = false;
            this.groupBox_DateTime.Text = "Date Time Update";
            // 
            // timer_sec
            // 
            this.timer_sec.Enabled = true;
            this.timer_sec.Interval = 1000;
            this.timer_sec.Tick += new System.EventHandler(this.timer_sec_Tick);
            // 
            // groupBox_COM
            // 
            this.groupBox_COM.Controls.Add(this.button_Disconnect);
            this.groupBox_COM.Controls.Add(this.label_COMstatus);
            this.groupBox_COM.Controls.Add(this.textBox_RunText);
            this.groupBox_COM.Controls.Add(this.comboBox_COM);
            this.groupBox_COM.Controls.Add(this.button_RunText);
            this.groupBox_COM.Controls.Add(this.button_Connect);
            this.groupBox_COM.Location = new System.Drawing.Point(12, 12);
            this.groupBox_COM.Name = "groupBox_COM";
            this.groupBox_COM.Size = new System.Drawing.Size(241, 154);
            this.groupBox_COM.TabIndex = 15;
            this.groupBox_COM.TabStop = false;
            this.groupBox_COM.Text = "COM Port";
            // 
            // button_Disconnect
            // 
            this.button_Disconnect.Location = new System.Drawing.Point(138, 108);
            this.button_Disconnect.Name = "button_Disconnect";
            this.button_Disconnect.Size = new System.Drawing.Size(75, 23);
            this.button_Disconnect.TabIndex = 11;
            this.button_Disconnect.Text = "Disconnect";
            this.button_Disconnect.UseVisualStyleBackColor = true;
            this.button_Disconnect.Click += new System.EventHandler(this.button_Disconnect_Click);
            // 
            // label_COMstatus
            // 
            this.label_COMstatus.AutoSize = true;
            this.label_COMstatus.Location = new System.Drawing.Point(7, 108);
            this.label_COMstatus.Name = "label_COMstatus";
            this.label_COMstatus.Size = new System.Drawing.Size(76, 13);
            this.label_COMstatus.TabIndex = 10;
            this.label_COMstatus.Text = "not connected";
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "pled";
            this.openFileDialog.Filter = "data file (*.pled)|*.pled";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog_FileOk);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.DefaultExt = "pled";
            this.saveFileDialog.Filter = "data file (*.pled)|*.pled";
            this.saveFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog_FileOk);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(780, 518);
            this.Controls.Add(this.groupBox_COM);
            this.Controls.Add(this.groupBox_DateTime);
            this.Controls.Add(this.groupBox_Led);
            this.Controls.Add(this.panel_led);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(800, 560);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "pLED-2014";
            this.SizeChanged += new System.EventHandler(this.MainForm_SizeChanged);
            this.panel_led.ResumeLayout(false);
            this.panel_led.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scale)).EndInit();
            this.groupBox_Led.ResumeLayout(false);
            this.groupBox_DateTime.ResumeLayout(false);
            this.groupBox_DateTime.PerformLayout();
            this.groupBox_COM.ResumeLayout(false);
            this.groupBox_COM.PerformLayout();
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
        private System.Windows.Forms.TextBox textBox_RunText;
        private System.Windows.Forms.Button button_RunText;
        private System.Windows.Forms.ComboBox comboBox_COM;
        private System.Windows.Forms.Button button_Connect;
        private System.Windows.Forms.TextBox textBox_Date;
        private System.Windows.Forms.TextBox textBox_Time;
        private System.Windows.Forms.Button button_Update;
        private System.Windows.Forms.GroupBox groupBox_Led;
        private System.Windows.Forms.GroupBox groupBox_DateTime;
        private System.Windows.Forms.Timer timer_sec;
        private System.Windows.Forms.GroupBox groupBox_COM;
        private System.Windows.Forms.Label label_COMstatus;
        private System.Windows.Forms.Button button_Disconnect;
        private System.Windows.Forms.Button button_Load;
        private System.Windows.Forms.Button button_Save;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
    }
}

