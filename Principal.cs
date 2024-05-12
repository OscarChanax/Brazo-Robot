using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using mamth
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Proyecto_3
{
    public partial class Principal : Form
    {
   
        System.IO.Ports.SerialPort Arduino; // Declarar la variable serialPort
        int brilloLed;
        public Principal()
        {
            InitializeComponent();
            //Form
            this.Text = string.Empty;
           // this.ControlBox = false;
            this.DoubleBuffered = true;

            //Inicializa puerto
            //Los Puertos se muestran en el ComboBox
            string[] ports = SerialPort.GetPortNames();
            comboBoxPuerto.Items.AddRange(ports);

            estadoPanel.BackColor = Color.Red;


        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
         
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Cuando se presiona el botón desconectar
            //Habilitacion del boton conectar
            buttonConectar.Enabled = true;
            estadoPanel.BackColor = Color.Red;

            if (Arduino.IsOpen)      //Si el puerto esta habierto
            {
                Arduino.Close();      //Desconecta el Puerto
            } 
        }

        private void comboBoxPuerto_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void buttonConectar_Click(object sender, EventArgs e)
        {
            if (comboBoxPuerto.SelectedItem != null)
            {
                string selectedPort = comboBoxPuerto.SelectedItem.ToString();

                try
                {
                    Arduino = new SerialPort(selectedPort, 9600); // Crear la instancia de SerialPort
                    Arduino.Open();
                    buttonConectar.Enabled = false;
                   // Estado de la conexion panel
                   estadoPanel.BackColor = Color.Green;
                    //Comunicación con Arduino a través de Arduino
                    // Por ejemplo, enviar datos a Arduino: Arduino.WriteLine("Hola, Arduino!");
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error al abrir el puerto COM: " + ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Por favor, selecciona un puerto COM antes de conectar.");
            }
        }

        private void Principal_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Arduino.Write("E");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Arduino.Write("F");
        }

        private void Principal_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (Arduino.IsOpen) 
            {
                Arduino.Close();
            }
          
        }

        private void buttonConectar_BackColorChanged(object sender, EventArgs e)
        {

        }

     

        private void labelValorhorizontal_Click(object sender, EventArgs e)
        {

        }
    

        private void panel3_Paint(object sender, PaintEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void buttonCalcular_Click(object sender, EventArgs e)
        {
            double a1 = 0;
            double a2 = 0;
            double Px = 0;
            double Py = 0;

            //Variables para almacenamiento de datos del efector final
            double Q1 = 0;
            double Q2 = 0;
            


            //Obtengo los valores
            a1 = double.Parse(textBoxA1.Text);
            a2 = double.Parse(textBoxA2.Text);
            Px = double.Parse(textBoxPx.Text);
            Py = double.Parse(textBoxPy.Text);


            
            


            //Formula Q2 Para efector Final

            Q2 = -Math.Acos((Math.Pow(Px,2)+Math.Pow(Py,2)-Math.Pow(a1,2)-Math.Pow(a2,2))/(2*a1*a2));


            //Formula Q1 Para efector Final

            Q1 = Math.Atan(Py / Px) + Math.Atan((a2 * Math.Sin(Q2)) / (a1 + a2 * Math.Cos(Q2)));



            // Convertir radianes a grados
            double q2 = Q2 * (180.0 / Math.PI);

            // Convertir radianes a grados
            double q1 = Q1 * (180.0 / Math.PI);

            // Muestra una ventana emergente
            MessageBox.Show("El valor de q2 es: " + q2.ToString());


            // Muestra una ventana emergente
            MessageBox.Show("El valor de q1 es: " + q1.ToString());

            // Muestra una ventana emergente
            MessageBox.Show("El valor de a1 es: " + a1.ToString());

            // Muestra una ventana emergente
            MessageBox.Show("El valor de a1 es: " + Px.ToString());

            //Envio los datos a arduino
            // !!IMPORTANTE LOS DATOS QUE SE ENVIAN SON DATOS CON SEPARADOR DECIMAL PUNTO DE LO
            // !!CONTRARIO NO SE REALIZARA UNA CORRECTA CONVERSION DE DATOS A DOUBLE¡¡

            Arduino.WriteLine(q1.ToString(System.Globalization.CultureInfo.InvariantCulture) +","+q2.ToString(System.Globalization.CultureInfo.InvariantCulture)+
                ","+ a1.ToString(System.Globalization.CultureInfo.InvariantCulture)+","+ a2.ToString(System.Globalization.CultureInfo.InvariantCulture)+
                ","+ Px.ToString(System.Globalization.CultureInfo.InvariantCulture) + "," + Py.ToString(System.Globalization.CultureInfo.InvariantCulture));
           // Arduino.WriteLine(q2.ToString());
            


        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Arduino.Write("hola mundo");
        }
    }
}
