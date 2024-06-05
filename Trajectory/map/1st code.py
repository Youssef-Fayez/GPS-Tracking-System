import folium 
import pandas as pd 

# Sample data (replace with your actual data)
data = {'lat': [30.0924435, 30.0919103, 30.0920670], 'lon': [31.02479416, 31.2484093, 31.2490265]}
df = pd.DataFrame(data)

# Create a map centered on the first point with a zoom level of 13
m = folium.Map(location=[df.iloc[0]['lat'], df.iloc[0]['lon']], zoom_start=13)

# Feature group to hold trajectory markers
trajectory = folium.FeatureGroup(name="My Trajectory")

# Add markers for each data point
for index, row in df.iterrows():
  marker = folium.Marker([row['lat'], row['lon']])
  trajectory.add_child(marker)  # Using add_child for each marker

# Add the trajectory layer to the map
m.add_child(trajectory)  # Using add_child for the FeatureGroup

# Generate HTML file
m.save("trajectory.html")

print("Trajectory map saved as trajectory.html")