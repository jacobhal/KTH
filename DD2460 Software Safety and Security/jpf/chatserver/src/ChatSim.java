/**
 * Sim/"driver" program for the Chat client/server example.
 */
import java.io.*;

public class ChatSim extends Thread {
    static int nClients = 2;
    static int nClientsServed = 2;
    //static final int portNumber = 4444 % java.net.Socket.NPORTS;

    public static final void main(String[]args) {
    // EXERCISE: Start server in separate thread
    String[] servArgs = new String[1];
    servArgs[0] = Integer.toString(nClientsServed);
    Thread server = new CentralizedProcess(0) {
      public void run() {
        try {
          ChatServer.main(servArgs);
        } catch (IOException e) {
          System.out.println("OMG!!!!!");
        }
      }
    };
    server.start();

    // wait for server to be ready (only possible in centralized version)
    try {
        synchronized (java.net.Socket.port) {
        while (!java.net.Socket.port.isOpen) {
            java.net.Socket.port.wait();
        }
        }
    } catch (InterruptedException e) {
    
    }
      for (int i = 1; i <= nClients; i++) {
      // EXERCISE: start clients in separate threads
        new CentralizedProcess(i) {
          public void run() {
            ChatClient.main(null);
          }
        }.start(); 
      }
    }
}