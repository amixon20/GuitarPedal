function[y, Fs] = chorusEffect(x, fs, depth, rate, delayTime, feedback)
% Chorus effect for guitar pedal plug in
% Alex Mixon

    % depth: depth of the modulation (0 to 1)
    % rate: modulation rate (in Hz)
    % delayTime: delay time of the chorus (in seconds)
    % feedback: feedback gain (0 to 1)
    
    % Convert delay time to samples
    delaySamples = round(delayTime * fs);
    
    % Create modulation signal
    t = (0:length(x)-1) / fs;
    modulation = depth * sin(2*pi*rate*t);
    
    N = length(x);
    % Initialize output signal
    y = zeros(N, 1);
   
    
    % Apply chorus effect
    for n = 1:N
        % Calculate delayed indices
        delayIndex = round(n - delaySamples * (1 + modulation(n)));
        
        % Apply feedback
        if delayIndex > 0 && delayIndex <= N
            y(n) = x(n) + feedback * x(delayIndex);
        else
            y(n) = x(n);
        end
    end
end