# Draw graph from csv file
import random
import pandas as pd
import matplotlib.pyplot as plt

def random_color():
    return (random.random(), random.random(), random.random())

if __name__ == '__main__':
    # Read csv content
    csv_file = "points.csv"
    df = pd.read_csv(csv_file)

    # Split data
    x = df['x']
    y = df['y']
    groups = df['gid'].unique()

    # Plot
    for i, group in enumerate(groups):
        subset = df[df['gid'] == group]
        plt.scatter(subset['x'], subset['y'],
                    s=10,
                    alpha=0.7,
                    color=random_color())

    plt.title("Points")
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.show()
