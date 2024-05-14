% Pedal Distortion Test
% Alex Mixon

clear; clc; 

[x, Fs] = audioread("AcGtr.wav");

% Drive: 1-10
drive = 10;

% Mix: 0-100
mix = 100;

% Filter freq for highpass
filter = 200;

[y, Fs] = pedalDistortion(x, Fs, drive, mix, filter);

sound(y, Fs);
