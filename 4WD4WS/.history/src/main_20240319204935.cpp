/*
 * @file main.cpp
 * @Jhih-Bin Huang (F112102103@nkust.edu.tw)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 * Input argument:
 *    Robot_yaw -> 轉彎角度
 *    v -> 車體速度
 */
#include "BaseControllerSetting.h"
#include "transmission.h"

void setup()
{
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(BLDC_R_PWM, OUTPUT);
  pinMode(BLDC_L_PWM, OUTPUT);
  pinMode(BLDC_R_rev, OUTPUT);
  pinMode(BLDC_L_rev, OUTPUT);
  pinMode(Encoder_R, OUTPUT);
  pinMode(Encoder_L, OUTPUT);

  RightStepper.setMaxSpeed(3200);
  RightStepper.setSpeed(1600);
  LeftStepper.setMaxSpeed(3200);
  LeftStepper.setSpeed(1600);

  steppers.addStepper(RightStepper);
  steppers.addStepper(LeftStepper);

  ledcSetup(0, 5000, 10);
  ledcAttachPin(BLDC_R_PWM, 0);

  ledcSetup(1, 5000, 10);
  ledcAttachPin(BLDC_L_PWM, 1);

  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  allocator = rcl_get_default_allocator();
    

  Twist.linear.x = 0;
  Twist.linear.y = 0;
  Twist.linear.z = 0;
  Twist.angular.x = 0;
  Twist.angular.y = 0;
  Twist.angular.z = 0;

  Serial.println("Setup Finish");
}

void loop()
{
  // if(Serial.available() > 0)
  // {
  //   Angle = Serial.parseInt();
  //   AckermannSteering(Angle);

  //   Pulse[0] = RobotSteer.thetaR / Pulse2Deg;
  //   Pulse[1] = RobotSteer.thetaL / Pulse2Deg;
  // }

  // steppers.moveTo(Pulse);
  // steppers.runSpeedToPosition();
  // delay(1000);

  ledcWrite([15:36:05.643] Running script with connection command: "C:\WINDOWS\System32\OpenSSH\ssh.exe" -T -D 51538 "LattePanda" bash
[15:36:05.645] Terminal shell path: C:\WINDOWS\System32\cmd.exe
[15:36:05.944] > C:\\Users\\ced22283/.ssh/config: line 2: Bad configuration option: hoistname
> C:\\Users\\ced22283/.ssh/config: terminating, 1 bad configuration options
> µ{§Ç¹Á¸Õ¼g¤J¨ì¤@­Ó¤£¦s¦bªººÞ¹D¡C
> ]0;C:\WINDOWS\System32\cmd.exe
[15:36:05.945] Got some output, clearing connection timeout
[15:36:07.240] "install" terminal command done
[15:36:07.241] Install terminal quit with output: ]0;C:\WINDOWS\System32\cmd.exe
[15:36:07.241] Received install output: ]0;C:\WINDOWS\System32\cmd.exe
[15:36:07.241] Failed to parse remote port from server output
[15:36:07.243] Resolver error: Error: 
	at g.Create (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:499734)
	at t.handleInstallOutput (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:497056)
	at t.tryInstall (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:620589)
	at async c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:580447
	at async t.withShowDetailsEvent (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:583753)
	at async k (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:577412)
	at async t.resolve (c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:581124)
	at async c:\Users\ced22283\.vscode\extensions\ms-vscode-remote.remote-ssh-0.109.0\out\extension.js:2:847283
[15:36:07.251] ------

}

void AckermannSteering(float Robot_yaw)
{
  double thetaR, thetaL;
  Robot_yaw = Robot_yaw * (PI / 180);
  if (Robot_yaw != 0)
  {
    RobotSteer.R = (RobotSteer.L / 2) / tan(Robot_yaw);
    RobotSteer.thetaR = atan(RobotSteer.L / (RobotSteer.R - (RobotSteer.T / 2))) * (180 / PI);
    RobotSteer.thetaL = -atan(RobotSteer.L / (RobotSteer.R + (RobotSteer.T / 2))) * (180 / PI);

  }
  else if (Robot_yaw == 0)
  {
    RobotSteer.thetaR = 0;
    RobotSteer.thetaL = 0;
  }

}

void ROSTimer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
  RCLC_UNUSED(last_call_time);

}