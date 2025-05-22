% Matthew Windsor
% 5/5/2024
% ELEC 3355 Final Project

% Set up audio input
audioInput = audioDeviceReader('SampleRate', 48000); 
setup(audioInput);
fs = audioInput.SampleRate;
% Set up audio output
audioOutput = audioDeviceWriter('SampleRate', 48000); 
% Open Com port to send data
delete(instrfind({'Port'},{'COM3'}));
arduino = serial('COM3', 'BaudRate', 9600);
fopen(arduino);
% Open files to store input and time data
filename = 'data.csv';
fileID = fopen(filename,'w');
filename2 = 'time.csv';
fileID2 = fopen(filename2,'w');
% Initialize arrays to store input and time data
frequency_data = []; % Store frequency values
time_data = []; % Store time stamps
% Plot
figure_handle = figure;
plot_handle = plot(NaN, NaN);
xlabel('Time');
ylabel('Frequency (Hz)');
title('Frequency vs Time');
grid on;
% Start counting time
startTime = tic;

% Start real time loop
try
    while true
        
        % Capture audio data
        audioData = audioInput();
        % Perform pitch detection
        winLength = min(round(fs*0.052), size(audioData, 1)); 
        overlapLength = min(round(0.045 * fs), winLength - 1); 
        [f0, ~] = pitch(audioData, fs, 'Method', 'SRH', 'WindowLength', winLength, 'OverlapLength', overlapLength);
        % Display the main frequency
        mainFrequency = mode(f0); % Extract the mode 
        disp(['Main Frequency: ', num2str(mainFrequency), ' Hz']);
        % Store frequency and time stamps in arrays
        frequency_data = [frequency_data; mainFrequency];
        time_data = [time_data; toc(startTime)]; % Time since start
        % Update plot
        set(plot_handle, 'XData', time_data, 'YData', frequency_data);
        drawnow; % Update plot
        % Write frequency data to text file
        fprintf(fileID, '%f\n', mainFrequency);
        % Write time data to text file
        fprintf(fileID2, '%f\n', toc(startTime));
        % Send the frequency data as a float via serial to arduino
        fprintf(arduino,'%f',mainFrequency);
        % Output audio 
        audioOutput(audioData);

    end
catch ex
    disp('Error occurred:');
    disp(ex.message);
end

% Clean up
fclose(fileID);
fclose(fileID2);
fclose(arduino);
release(audioInput);
release(audioOutput);




