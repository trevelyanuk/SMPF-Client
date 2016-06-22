using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConfigTool
{
    public partial class Form1 : Form
    {
        //Writing to a text file in C# - https://msdn.microsoft.com/en-us/library/8bh11f1k.aspx?f=255&MSPPError=-2147217396


        String[,] configOptions; 

        char[] delimiters = {'=', '\n', ';'};
        String[] lines;
        int q = 0;
        String[][] variables;


        public Form1()
        {
            InitializeComponent();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            openFileDialog1.FileName = "config.ini";
            openFileDialog1.ShowDialog();
           // if (openFileDialog1.)
            lines = System.IO.File.ReadAllLines(@openFileDialog1.FileName);
            variables = new String[lines.Count()][];

            foreach (String line in lines)
            {
                variables[q++] = line.Split(delimiters);
            }

            processVariablesIn();
            q = 0;
        }

        private void buttonCreate_Click(object sender, EventArgs e)
        {
            saveFileDialog1.FileName = "config.ini";
            saveFileDialog1.ShowDialog();

            string localUse = "local = ";
            if (checkLocal.Checked == false)
            {

                localUse = "";
            }
            else if (radioCSV.Checked)
            {
                localUse += "CSV";
            }
            else if (radioSimple.Checked)
            {
                localUse += "SIMPLE";
            }

            string[] configFile = {
                "server = " + textServerAddress.Text,
                "page = " + textPage.Text,
                "network = " + textNetwork.Text,
                "timeout = " + textTimeout.Text,
                "protolldp = " + checkCDP.Checked.ToString().ToLower(),
                "protocdp = " + checkCDP.Checked.ToString().ToLower(),
                localUse};

            System.IO.File.WriteAllLines(saveFileDialog1.FileName, configFile);


        }
        
        private void buttonExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void processVariablesOut()
        {
        }

        private void processVariablesIn()
        {
            foreach (string[] line in variables)
            {
                String tempString = line[0].Trim(' ');
                tempString.ToLower();

                switch (tempString)
                {
                    case "server":
                        {
                            textServerAddress.Text = line[1].ToLower().Trim(' ');
                            break;
                        }
                    case "network":
                        {
                            textNetwork.Text = line[1].ToLower().Trim(' ');
                            break;
                        }
                    case "page":
                        {
                            textPage.Text = line[1].ToLower().Trim(' ');
                            break;
                        }
                    case "timeout": 
                        {
                            textTimeout.Text = line[1].ToLower().Trim(' ');
                            break;
                        }
                    case "protolldp":
                        {
                            if ((line[1] == "0") || (line[1].ToLower() == "false") || (line[1].ToLower() == "no"))
                            {
                                checkLLDP.Checked = false;
                            }
                            else
                            {
                                checkLLDP.Checked = true;
                            }
                            break;
                        }
                    case "protocdp":
                        {
                            if ((line[1] == "0") || (line[1].ToLower() == "false") || (line[1].ToLower() == "no"))
                            {
                                checkCDP.Checked = false;
                            }
                            else
                            {
                                checkCDP.Checked = true;
                            }
                            break;
                        }
                    default: break;
                }
            }
        }

        private void checkLocal_CheckedChanged(object sender, EventArgs e)
        {
            radioSimple.Enabled = !radioSimple.Enabled;
            radioCSV.Enabled = !radioCSV.Enabled;
            textServerAddress.Enabled = !textServerAddress.Enabled;
            textPage.Enabled = !textPage.Enabled;
        }
    }
}
