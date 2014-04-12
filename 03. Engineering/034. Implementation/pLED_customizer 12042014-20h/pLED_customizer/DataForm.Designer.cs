namespace pLED_customizer
{
    partial class DataForm
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
            this.textBox_data = new System.Windows.Forms.TextBox();
            this.button_update = new System.Windows.Forms.Button();
            this.button_hide = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_data
            // 
            this.textBox_data.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.textBox_data.Location = new System.Drawing.Point(0, 41);
            this.textBox_data.Multiline = true;
            this.textBox_data.Name = "textBox_data";
            this.textBox_data.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox_data.Size = new System.Drawing.Size(384, 481);
            this.textBox_data.TabIndex = 0;
            // 
            // button_update
            // 
            this.button_update.Location = new System.Drawing.Point(12, 12);
            this.button_update.Name = "button_update";
            this.button_update.Size = new System.Drawing.Size(75, 23);
            this.button_update.TabIndex = 1;
            this.button_update.Text = "Update";
            this.button_update.UseVisualStyleBackColor = true;
            this.button_update.Click += new System.EventHandler(this.button_update_Click);
            // 
            // button_hide
            // 
            this.button_hide.Location = new System.Drawing.Point(297, 12);
            this.button_hide.Name = "button_hide";
            this.button_hide.Size = new System.Drawing.Size(75, 23);
            this.button_hide.TabIndex = 2;
            this.button_hide.Text = "Hide";
            this.button_hide.UseVisualStyleBackColor = true;
            this.button_hide.Click += new System.EventHandler(this.button_hide_Click);
            // 
            // DataForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 522);
            this.ControlBox = false;
            this.Controls.Add(this.button_hide);
            this.Controls.Add(this.button_update);
            this.Controls.Add(this.textBox_data);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "DataForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "DataForm";
            this.VisibleChanged += new System.EventHandler(this.DataForm_VisibleChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_data;
        private System.Windows.Forms.Button button_update;
        private System.Windows.Forms.Button button_hide;
    }
}