import sys

def nrz_l(data):
    signal = []
    for bit in data:
        if bit == '0':
            signal.append('+V')
        elif bit == '1':
            signal.append('-V')
    return signal

def nrz_i(data):
    signal = []
    level = '+V'
    if data[0] == '1':
        level = '-V'
    signal.append(level)
    
    for i in range(1, len(data)):
        if data[i] == '1':
            level = '-V' if level == '+V' else '+V'
        signal.append(level)
    return signal

def manchester(data):
    signal = []
    for bit in data:
        if bit == '0':
            signal.append('+V -> -V')
        elif bit == '1':
            signal.append('-V -> +V')
    return signal

def diff_manchester(data):
    signal = []
    last_level = '+V'
    
    for bit in data:
        if bit == '0':
            transition = f"{last_level} -> {'-V' if last_level == '+V' else '+V'}"
            signal.append(transition)
            last_level = '-V' if last_level == '+V' else '+V'
        elif bit == '1':
            transition = f"{last_level} -> {last_level}"
            signal.append(transition)
        
        transition_mid = f"{signal[-1].split(' ')[-1]} -> {'-V' if signal[-1].split(' ')[-1] == '+V' else '+V'}"
        signal[-1] = f"{signal[-1].split(' ')[0]} -> {transition_mid.split(' ')[-1]}"
        last_level = transition_mid.split(' ')[-1]
        
    final_signal = []
    last_end = '+V'
    if data[0] == '0':
        final_signal.append(f"+V -> -V")
        last_end = '-V'
    else: # data[0] == '1'
        final_signal.append(f"+V -> +V")
        last_end = '+V'

    for i in range(1, len(data)):
        if data[i] == '0': # Transition at start
            start = '-V' if last_end == '+V' else '+V'
            end = '-V' if start == '+V' else '+V'
            final_signal.append(f"{start} -> {end}")
            last_end = end
        else: # No transition at start
            start = last_end
            end = '-V' if start == '+V' else '+V'
            final_signal.append(f"{start} -> {end}")
            last_end = end
            
    return final_signal


def ami(data):
    signal = []
    last_pulse = '-V'
    for bit in data:
        if bit == '0':
            signal.append(' 0 ')
        elif bit == '1':
            if last_pulse == '-V':
                signal.append('+V')
                last_pulse = '+V'
            else:
                signal.append('-V')
                last_pulse = '-V'
    return signal

def print_menu():
    print("\n--- Line Encoding Schemes ---")
    print("1. NRZ-L")
    print("2. NRZ-I")
    print("3. Manchester")
    print("4. Differential Manchester")
    print("5. AMI (Alternate Mark Inversion)")
    print("6. Exit")
    print("-----------------------------")

def main():
    while True:
        print_menu()
        choice = input("Enter your choice (1-6): ")

        if choice == '6':
            print("Exiting...")
            break
        
        if choice not in ['1', '2', '3', '4', '5']:
            print("Invalid choice. Please try again.")
            continue

        data = input("Enter binary data string (e.g., 010011): ")
        if not all(c in '01' for c in data):
            print("Invalid data. Please enter only '0's and '1's.")
            continue
        
        signal = []
        scheme = ""

        if choice == '1':
            scheme = "NRZ-L"
            signal = nrz_l(data)
        elif choice == '2':
            scheme = "NRZ-I"
            signal = nrz_i(data)
        elif choice == '3':
            scheme = "Manchester"
            signal = manchester(data)
        elif choice == '4':
            scheme = "Differential Manchester"
            signal = diff_manchester(data)
        elif choice == '5':
            scheme = "AMI"
            signal = ami(data)
        
        print(f"\nScheme: {scheme}")
        print(f"Data:   {'  |  '.join(data)}")
        print(f"Signal: {' | '.join(signal)}")


if __name__ == "__main__":
    main()