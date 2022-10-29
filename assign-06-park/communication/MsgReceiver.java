//package communication;

import jssc.*;

import java.nio.charset.StandardCharsets;

public class MsgReceiver {
	
	final private SerialComm port;
	byte b;

	public MsgReceiver(String portname) throws SerialPortException {
		port = new SerialComm(portname);
	}

	public byte[] timeArray = new byte[4];
	public byte[] potArray = new byte[] {0x00, 0x00, 0x00, 0x00};
	public byte[] ultraArray = new byte[4];
	public byte[] stringArray = new byte[100];
	public byte[] stringLengthArray = new byte[] {0x00, 0x00, 0x00, 0x00};
	public byte[] stringArray1 = new byte[100];
	public byte[] stringLengthArray1 = new byte[] {0x00, 0x00, 0x00, 0x00};
	public int timestamp;
	public int timestampCounter = 0;
	public int potValue;
	public int potCounter = 0;
	public int ultraValue;
	public int ultraCounter = 0;
	public int stringErrorLengthCounter = 0;
	public int stringErrorLength;
	public int stringLengthCounter = 0;
	public int stringLength;


	public void run() throws SerialPortException {
		// insert FSM code here to read msgs from port
		// and write to console
		String state = "wait";
		while(true) {
			if(port.available()) {
				b = port.readByte();
				switch (state) {
					case "wait":
						if(b==0x21) {
							state = "magic";
						}
						break;
					case "magic":
						if(b==0x32) {
							state = "timestamp";
						}else if(b==0x33) {
							state = "pot";
						}else if(b==0x34) {
							state = "ultra";
						}else if(b==0x31) {
							state = "get length error";
						}else if(b==0x30) {
							state = "get length";
						}else {
							state = "error";
						}
						break;
					case "timestamp":
						if(timestampCounter < 3) {
							timeArray[timestampCounter] = b;
							timestampCounter++;
						}else {
							timeArray[3] = b;
							for (byte a : timeArray) {
								timestamp = (timestamp << 8) + (a & 0xFF);
							}
							System.out.println("Timestamp: " + timestamp + " ms");
							state = "wait";
							timestampCounter = 0;
						}
						break;
					case "pot":
						if(potCounter < 1) {
							potArray[potCounter + 2] = b;
							potCounter++;
						}else {
							potArray[3] = b;
							for (byte a : potArray) {
								potValue = (potValue << 8) + (a & 0xFF);
							}
							System.out.println("Potentiometer Value: " + potValue);
							state = "wait";
							potCounter = 0;
						}
						break;
					case "ultra":
						if(ultraCounter < 3) {
							ultraArray[ultraCounter] = b;
							ultraCounter++;
						}else {
							ultraArray[3] = b;
							for (byte a : ultraArray) {
								ultraValue = (ultraValue << 8) + (a & 0xFF);
							}
							System.out.println("Raw Ultrasonic Value: " + ultraValue);
							System.out.println("Distance from object: " + (ultraValue*0.5*343/10000) + " cm");
							System.out.println("-------------------------");
							state = "wait";
							ultraCounter = 0;
						}
						break;
					case "get length error":
						if(stringErrorLengthCounter < 1) {
							stringLengthArray[stringErrorLengthCounter +2] = b;
							stringErrorLengthCounter++;
						}else {
							stringLengthArray[3] = b;
							for(byte a: stringLengthArray) {
								stringErrorLength = (stringErrorLength <<8) + (a & 0xFF);
							}
							state = "read string error";
							stringErrorLengthCounter = 0;
						}
						break;
					case "read string error":
						if(stringErrorLengthCounter < stringErrorLength - 1) {
							stringArray[stringErrorLengthCounter] = b;
							stringErrorLengthCounter++;
						}else {
							stringArray[stringErrorLength - 1] = b;
							byte[] shortened = new byte[stringErrorLength];
							System.arraycopy(stringArray, 0, shortened, 0, stringErrorLength);
							String reconstruct = new String(shortened, StandardCharsets.UTF_8);
							System.out.println("Error: " + reconstruct);
							System.out.println("=========================");
							stringErrorLengthCounter = 0;
							state = "wait";
						}
						break;
					case "get length":
						if(stringLengthCounter < 1) {
							stringLengthArray1[stringLengthCounter +2] = b;
							stringLengthCounter++;
						}else {
							stringLengthArray1[3] = b;
							for(byte a: stringLengthArray1) {
								stringLength = (stringLength <<8) + (a & 0xFF);
							}
							state = "read string";
							stringLengthCounter = 0;
						}
						break;
					case "read string":
						if(stringLengthCounter < stringLength - 1) {
							stringArray1[stringLengthCounter] = b;
							stringLengthCounter++;
						}else {
							stringArray1[stringLength - 1] = b;
							byte[] shortened = new byte[stringLength];
							System.arraycopy(stringArray1, 0, shortened, 0, stringLength);
							String reconstruct = new String(shortened, StandardCharsets.UTF_8);
							System.out.println("String: " + reconstruct);
							stringLengthCounter = 0;
							state = "wait";
						}
						break;
					case "error":
						System.out.println("Error: Unknown Key Used.");
						state = "wait";
						break;
				}
			}
		}

	}

	public static void main(String[] args) throws SerialPortException {
		MsgReceiver msgr = new MsgReceiver("COM4"); // Adjust this to be the right port for your machine
		msgr.port.setDebug(false);
		msgr.run();
	}
}
