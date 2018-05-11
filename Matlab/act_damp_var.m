% variables and velocoty plot for active damper
% all are in English Units
clear all
clc
close all

Jmotor   = 1.9e-3;      % sec polar inertia
Ra       = 0.7;         % thev res of armature
Kt       = 2.0336e5;    % compliance of shaft
rp       = 0.75;        % radius of pin
mc       = 1;           % mass cart C
mb       = 1;           % mass cart B
ma       = 1;           % mass cart A
Kb       = 2.284;       % spring constant lbf/in
Ka       = 2.284;       % spring constant lbf/in
La       = 9.05e-4;     % inductance of motor
Kphi     = 4.9e-3;      % Motor constant
endTime  = 50;
SampTime = 0.02;

sim('Active_Damping', endTime)

figure(1)
clf
plot(time,Vb)
title('Velocity on cart B as a function of time')
xlabel('Time (s)')
ylabel('Velocity in/s')