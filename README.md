## abst

![image](https://github.com/user-attachments/assets/e3818470-836a-487c-a5d6-98de479663a6)



This simulation uses a simplified version of the wave equation. The following are the main points

1. lattice model:
   The water surface is represented as a two-dimensional grid. Each grid point represents the height of the water surface. 2.

2. time evolution:
   Two arrays, `current` and `previous`, are used to represent the state of the water surface at each time step. 3.

3. wave propagation:
   The new height of each grid point is calculated based on the average of the eight surrounding points. This is done in the following lines

   ```cpp
   current[i][j] = (previous[i-1][j] + previous[i+1][j] +
                    previous[i][j-1] + previous[i][j+1] +
                    previous[i-1][j-1] + previous[i-1][j+1] +
                    previous[i+1][j-1] + previous[i+1][j+1]) / 4 - current[i][j];
   ````

   This calculation produces the vertical motion of the wave by averaging the effects from the surrounding points and subtracting the height of the current point.

4. damping:
   The ``damping`` factor (0.95) is used to simulate the loss of energy:

   ```cpp
   current[i][j] *= damping;.
   ```

   This causes the wave to gradually decrease in size over time.

5. initial conditions:
   At the start of the simulation, we are simulating a single “drop” in the center of the screen:

   ```cpp
   previous[screenHeight/2][screenWidth/2] = 255;
   ```

6. visualization:
   The movement of the water surface is visualized by mapping the height of each grid point as the intensity of the blue color.

This model is very simplified, but is sufficient to simulate the basic motion of the water surface. Actual water behavior is more complex, but this simulation captures the basic characteristics of ripples and interference patterns on the water's surface.


Translated with DeepL.com (free version)
