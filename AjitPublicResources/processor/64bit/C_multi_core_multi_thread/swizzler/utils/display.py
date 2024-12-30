import matplotlib.pyplot as plt

# Read data from mapped.txt and convert each line from hexadecimal to decimal
with open("addr_trace.txt", "r") as file:
    test_data = [int(line.strip(), 16) for line in file]  # Convert hex to decimal

# Print confirmation of file loading
print("File successfully loaded. The file has", len(test_data), "entries.")

# Create the figure and axis
fig, ax = plt.subplots(figsize=(10, 6))

# Plot the data
line, = ax.plot(test_data, label="Test Data (Addresses)", marker="o", linestyle="-", picker=5)  # Enable picking

# Adding labels and title
ax.set_xlabel("Index")
ax.set_ylabel("Address Value (Decimal)")
ax.set_title("Visualization of Addresses in mapped.txt (Converted to Decimal)")
ax.legend()
ax.grid(True)

# Enable pan/zoom for scrolling
plt.subplots_adjust(bottom=0.2)  # Adjust bottom margin for navigation bar
plt.xticks(rotation=45)  # Rotate x-axis labels for better visibility
ax.set_xlim(0, 500)  # Initial view limits for horizontal axis

# Function to update x-axis limits dynamically
def on_scroll(event):
    cur_xlim = ax.get_xlim()
    step = (cur_xlim[1] - cur_xlim[0]) * 0.2  # Step size for scrolling (20% of view range)
    if event.button == 'up':
        ax.set_xlim(cur_xlim[0] - step, cur_xlim[1] - step)
    elif event.button == 'down':
        ax.set_xlim(cur_xlim[0] + step, cur_xlim[1] + step)
    fig.canvas.draw_idle()

fig.canvas.mpl_connect('scroll_event', on_scroll)

# Function to display x and y coordinates on click
def on_pick(event):
    if event.artist == line:  # Check if the clicked artist is the line plot
        xdata, ydata = event.artist.get_data()
        ind = event.ind[0]  # Get the index of the clicked point
        x, y = xdata[ind], ydata[ind]
        print(f"Clicked on point: x={x}, y={y}")
        ax.annotate(f"({x}, {y})", (x, y), textcoords="offset points", xytext=(10, 10), ha='center', color="red")
        fig.canvas.draw_idle()

fig.canvas.mpl_connect('pick_event', on_pick)

# Show the plot with interactive features
plt.show()

