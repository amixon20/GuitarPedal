% Load audio file
[x, Fs] = audioread('AcGtr.wav');

% Define parameters
depth = 0.5; % Depth of tremolo effect (0 to 1)
frequency = 5; % Frequency of tremolo oscillation (Hz)

N = length(x);
% Generate time vector
t = (0:N-1) / Fs;

% Generate LFO
lfo = (1 + depth * sin(2*pi*frequency*t)).';

% Apply tremolo effect
y = input .* lfo;

% Normalize output
y = y / max(abs(output));

% Play processed audio
sound(y, Fs);