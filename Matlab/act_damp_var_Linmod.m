% variables and velocoty plot for active damper
% all are in English Units
clear all
clc
close all

Jmotor   = 1.9e-3;      % sec polar inertia
Ra       = 0.7;         % thev res of armature
Kt       = 2.0336e5;    % compliance of shaft
Rt       = 1;         % damping the compliance
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

% Run simulink model
% sim('Active_Damping', endTime)

[Amat, Bmat, Cmat, Dmat] = linmod('example');

smdSys = ss(Amat,Bmat,Cmat,Dmat)
 
tf(smdSys)
zpk(smdSys)
bode(smdSys)
grid on