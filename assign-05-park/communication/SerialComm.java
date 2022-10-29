package communication;

import jssc.*;
import java.util.Scanner;

public class SerialComm {

	SerialPort port;
	private boolean debug;
	private static byte b;

	public static void main(String[] args) throws SerialPortException {

		SerialComm port = new SerialComm("COM3");
		port.setDebug(false);
		byte reads;

		Scanner scanner = new Scanner(System.in);
		while(true) {
			System.out.print("Enter String to encode: ");
			String s = scanner.nextLine();
			byte[] bytes = s.getBytes();
			for(int i = 0; i < bytes.length ; i++) {
				port.writeByte(bytes[i]);
				boolean keepLooping = true;
				while(keepLooping) {
					if(port.available()) {
						b = port.readByte();
						if(b == 13 || b == 10) {
							System.out.print("");
						}else {
							char c = (char) b;
							System.out.print(c);
						}
					}
					if(b == 13) {
						keepLooping = false;
					}
				}
			}
			System.out.println("");
		}

	}
	// Indicator of "debugging mode"

	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}


	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);

		debug = false; // Default is to NOT be in debug mode
	}

	// TODO: Add writeByte() method to write data to serial port

	public void writeByte(byte by) throws SerialPortException {
		port.writeByte(by);
		if(debug) {
			System.out.print("Outgoing: " +"<0x" + String.format("%02x", by) + ">, ");
			System.out.println();
		}
	}

	public boolean available() throws SerialPortException {
		if(port.getInputBufferBytesCount() >= 1) {
			return true;
		}
		return false;
	}

	public byte readByte() throws SerialPortException {
		byte[] bArray;
		bArray = port.readBytes(1);
		if(debug) {
			System.out.println("Incoming: " + "<0x" + String.format("%02x", bArray[0]) + ">");
		}
		return bArray[0];
	}

}
