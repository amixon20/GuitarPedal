function [y, Fs] = pedalDistortion(x, Fs, drive, mix, filter)

% Guitar Pedal Distortion demo
% Alex Mixon

dry = x;

normDrive = drive/10;

filterSig = highpass(x, filter, Fs);

% Setting up loop for distortion
N = length(filterSig);

distWet = zeros(N,1);

% distWet = arctanDistortion(filterSig, drive)
for n = 1:N
    distWet(n,1) = normDrive * ((2/pi)*atan(filterSig(n,1)));
end

% Normalization of wet/dry balance
 mixNorm = mix/100;

y = mixNorm * distWet + (1-mixNorm) * dry;

% Normalize output
y = y / max(abs(y));

