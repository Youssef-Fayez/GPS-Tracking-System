import folium
import pandas as pd  
import serial

def read_floats_from_serial(ser, count):
    """
    Reads a specified number of float values from the serial port.
    
    Parameters:
    ser (serial.Serial): The serial port object.
    count (int): The number of float values to read.
    
    Returns:
    list: A list of float values.
    """
    floats = []
    while len(floats) < count:
        if ser.in_waiting > 0:
            try:
                data = ser.readline().decode('utf-8').strip()
                floats.append(float(data))
            except ValueError:
                print(f"Received invalid float: {data}")
    return floats

def read_arrays_from_uart(port, baudrate):
    """
    Reads LATITUDE and LONGITUDE arrays from a specified UART port.
    
    Parameters:
    port (str): The name of the UART port (e.g., '/dev/ttyS0' on Linux or 'COM3' on Windows).
    baudrate (int): The baud rate for the UART communication.
    
    Returns:
    tuple: Two lists containing LATITUDE and LONGITUDE values.
    """
    lats = []
    lons = []

    try:
        # Open the serial port
        ser = serial.Serial('COM5', 9600, timeout=1)
        print(f"Connected to {port} at {baudrate} baud.")

        # Read the length of the arrays
        while True:
            if ser.in_waiting > 0:
                try:
                    length = int(ser.readline().decode('utf-8').strip())
                    print(f"Array length: {length}")
                    break
                except ValueError:
                    print("Failed to read array length")

        # Read the LATITUDE array
        print("Reading LATITUDE array...")
        lats = read_floats_from_serial('COM5', length)
        print(f"Received LATITUDE: {lats}")

        # Read the LONGITUDE array
        print("Reading LONGITUDE array...")
        lons = read_floats_from_serial('COM5', length)
        print(f"Received LONGITUDE: {lons}")

    except serial.SerialException as e:
        print(f"Error opening or using serial port: {e}")

    finally:
        ser.close()
        print("Serial port closed.")

    return lats, lons

if __name__ == "__main__":
    # Replace '/dev/ttyS0' with your UART port and 9600 with your baud rate
    lats, lons = read_arrays_from_uart('COM5', 9600)

    # Print the received arrays
    print("LATITUDE array:", lats)
    print("LONGITUDE array:", lons)


def plot_trajectory(lons, lats):

  # Check if lengths match
  if len(lons) != len(lats):
    raise ValueError("Lengths of longitude and latitude arrays must be equal.")

  # Create a map centered on the first point with a default zoom level
  m = folium.Map(location=[lats[0], lons[0]], zoom_start=13)

  # Feature group for trajectory markers
  trajectory = folium.FeatureGroup(name="My Trajectory")

  # Add markers for each data point
  for lon, lat in zip(lons, lats):
    marker = folium.Marker([lat, lon])
    trajectory.add_child(marker)

  # Add the trajectory layer to the map
  m.add_child(trajectory)

  return m


# Example usage (replace with your actual data)
#lats = [30.063477, 30.062497]
#lons = [31.280888, 31.278209]


# Create the map
my_map = plot_trajectory(lons, lats)

# Optionally save the HTML file (uncomment the line below)
my_map.save("custom_trajectory.html")