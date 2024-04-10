import numpy as np
import matplotlib.pyplot as plt

def ackermann_steering(angle, wheelbase, turn_radius):
    """
    Calculate the steering angle for Ackermann steering geometry.
    angle: turning angle in radians
    wheelbase: distance between the front and rear axles
    turn_radius: desired turning radius
    """
    return np.arctan(wheelbase / (turn_radius - 0.5 * wheelbase * np.tan(angle)))

def plot_ackermann_motion(turn_radius, wheelbase):
    """
    Plot the trajectory of the wheels during Ackermann steering motion.
    turn_radius: desired turning radius
    wheelbase: distance between the front and rear axles
    """
    # Generate a range of turning angles
    angles = np.linspace(-np.pi / 2, np.pi / 2, 100)

    # Calculate steering angles for inner and outer wheels
    inner_steering = ackermann_steering(angles, wheelbase, turn_radius)
    outer_steering = ackermann_steering(angles, wheelbase, turn_radius + 0.5 * wheelbase)

    # Calculate trajectories for inner and outer wheels
    inner_x = turn_radius * np.cos(angles)
    inner_y = turn_radius * np.sin(angles)
    outer_x = (turn_radius + wheelbase) * np.cos(angles + inner_steering)
    outer_y = (turn_radius + wheelbase) * np.sin(angles + inner_steering)

    # Plot trajectories
    plt.plot(inner_x, inner_y, label='Inner Wheel')
    plt.plot(outer_x, outer_y, label='Outer Wheel')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Ackermann Steering Motion')
    plt.axis('equal')
    plt.legend()
    plt.grid(True)
    plt.show()

# Example usage
wheelbase = 750  # Distance between the front and rear axles
turn_radius = 40  # Desired turning radius

plot_ackermann_motion(turn_radius, wheelbase)
