% Load an audio file
[x, Fs] = audioread('AcGtr.wav');

% Set parameters
depth = 0.01;          % Depth of modulation
rate = 2;               % Modulation rate in Hz
delayTime = 0.05;      % Delay time in seconds
feedback = 0.3;         % Feedback gain

% Apply chorus effect
[y, Fs] = chorusEffect(x, Fs, depth, rate, delayTime, feedback);

% Play the output
sound(y, Fs);
