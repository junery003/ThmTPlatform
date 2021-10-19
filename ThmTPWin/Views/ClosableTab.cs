//-----------------------------------------------------------------------------
// File Name   : ClosableTab
// Author      : junlei
// Date        : 9/21/2021 8:55:14 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ThmTPWin.Views {
    public class ClosableTab : TabItem {
        public ClosableTab() {
            // Create an instance of the usercontrol
            ClosableHeader closableTabHeader = new();

            // Attach to the CloseableHeader events (Mouse Enter/Leave, Button Click, and Label resize)
            closableTabHeader.button_close.MouseEnter += new MouseEventHandler(button_close_MouseEnter);
            closableTabHeader.button_close.MouseLeave += new MouseEventHandler(button_close_MouseLeave);
            closableTabHeader.button_close.Click += new RoutedEventHandler(button_close_Click);
            closableTabHeader.label_TabTitle.SizeChanged += new SizeChangedEventHandler(label_TabTitle_SizeChanged);

            Header = closableTabHeader;
        }

        /// <summary>
        /// Property - Set the Title of the Tab
        /// </summary>
        public string Title {
            get => (string)((ClosableHeader)Header).label_TabTitle.Content;
            set => ((ClosableHeader)Header).label_TabTitle.Content = value;
        }

        // Button MouseEnter - When the mouse is over the button - change color to Red
        void button_close_MouseEnter(object sender, MouseEventArgs e) {
            ((ClosableHeader)Header).button_close.Foreground = Brushes.Red;
        }

        // Button MouseLeave - When mouse is no longer over button - change color back to black
        void button_close_MouseLeave(object sender, MouseEventArgs e) {
            ((ClosableHeader)Header).button_close.Foreground = Brushes.Black;
        }

        // Button Close Click - Remove the Tab - (or raise an event indicating a "CloseTab" event has occurred)
        void button_close_Click(object sender, RoutedEventArgs e) {
            ((TabControl)Parent).Items.Remove(this);
        }

        // Label SizeChanged - When the Size of the Label changes (due to setting the Title) set position of button properly
        void label_TabTitle_SizeChanged(object sender, SizeChangedEventArgs e) {
            ((ClosableHeader)Header).button_close.Margin = new Thickness(((ClosableHeader)Header).label_TabTitle.ActualWidth + 5, 3, 4, 0);
        }
    }
}
