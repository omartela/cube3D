# Cube3D - 3D Raycasting Game Engine

![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=flat-square&logo=opengl&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)

**Cube3D** is a 3D raycasting game engine inspired by the classic Wolfenstein 3D. This project implements a 3D perspective rendering engine using raycasting techniques, creating a pseudo-3D environment from a 2D map. Built as part of the 42 School curriculum, it features textured walls, sprites, collision detection, and an interactive game environment.

## 🎮 Features

- **3D Raycasting Engine**: Real-time 3D rendering using raycasting algorithms
- **Textured Walls**: Support for different wall textures (North, South, East, West)
- **Sprite System**: Animated enemies and interactive objects
- **Collision Detection**: Advanced circular collision detection system
- **Interactive Doors**: Doors that can be opened and closed
- **Mini-map**: 2D overhead view of the current level
- **Main Menu**: Intuitive main menu with options and controls
- **Attack System**: Combat mechanics with weapon animations
- **Custom Map Format**: Support for .cub map files

## 🚀 Getting Started

### Prerequisites

Before building the project, ensure you have the following dependencies installed:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev

# macOS (with Homebrew)
brew install cmake glfw

# Fedora/RHEL
sudo dnf install gcc make cmake glfw-devel mesa-libGL-devel mesa-libGLU-devel
```

### Installation

1. **Clone the repository:**
```bash
git clone https://github.com/omartela/cube3D.git
cd cube3D
```

2. **Build the project:**
```bash
make
```

The build process will automatically:
- Clone and compile the MLX42 graphics library
- Compile the custom libft library
- Build the main cub3D executable

3. **Run the game:**
```bash
./cub3D maps/easy.cub
```

## 🎯 Usage

### Basic Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Turn left |
| `→` | Turn right |
| `Space` | Attack/Interact |
| `ESC` | Exit game |

### Command Line

```bash
./cub3D [map_file.cub]
```

**Example:**
```bash
./cub3D maps/maze.cub
```

## 🗺️ Map Format

The game uses `.cub` files to define levels. Here's the structure:

### Map File Structure

```
NO ./pngs/texture_no.png    # North wall texture
SO ./pngs/texture_so.png    # South wall texture  
WE ./pngs/texture_we.png    # West wall texture
EA ./pngs/texture_ea.png    # East wall texture

F 220,100,0                 # Floor color (RGB)
C 225,30,0                  # Ceiling color (RGB)

1111111111
1000000001
1000N00001                  # N = Player start position (North)
1000000001
1111111111
```

### Map Elements

| Character | Description |
|-----------|-------------|
| `0` | Empty space (floor) |
| `1` | Wall |
| `2` | Door |
| `N` | Player start position (facing North) |
| `S` | Player start position (facing South) |
| `E` | Player start position (facing East) |
| `W` | Player start position (facing West) |

### Example Maps

The project includes several example maps in the `maps/` directory:

- `easy.cub` - Simple rectangular room
- `maze.cub` - Complex maze layout
- `door_map.cub` - Map featuring interactive doors

## 🏗️ Project Structure

```
cube3D/
├── src/                    # Source code files
│   ├── main.c             # Entry point and game loop
│   ├── raycasting.c       # Core raycasting algorithms
│   ├── keyboard.c         # Input handling
│   ├── mainmenu.c         # Main menu system
│   ├── minimap.c          # 2D minimap rendering
│   ├── sprites.c          # Sprite management
│   └── ...
├── inc/                   # Header files
│   └── cub3d.h           # Main header file
├── maps/                  # Example map files
├── pngs/                  # Texture and sprite assets
├── libft/                 # Custom C library
├── Makefile              # Build configuration
└── README.md
```

## 🛠️ Technical Details

### Raycasting Algorithm

The engine uses a ray-casting algorithm to render the 3D environment:

1. **Ray Casting**: Cast rays from the player's position for each column of pixels
2. **Wall Detection**: Detect intersections with walls using DDA algorithm
3. **Distance Calculation**: Calculate perpendicular distance to avoid fish-eye effect
4. **Wall Height**: Determine wall height based on distance
5. **Texture Mapping**: Apply appropriate wall textures

### Graphics Library

- **MLX42**: Modern graphics library providing OpenGL-based rendering
- **GLFW**: Cross-platform window and input handling
- **OpenGL**: Hardware-accelerated graphics rendering

### Performance Features

- **Efficient Rendering**: Optimized raycasting with minimal redundant calculations
- **Collision Detection**: Fast circular collision detection for smooth movement
- **Memory Management**: Careful memory allocation and cleanup

## 🧪 Testing

Test the game with different maps:

```bash
# Test basic functionality
./cub3D maps/easy.cub

# Test complex navigation
./cub3D maps/maze.cub

# Test door mechanics
./cub3D maps/door_map.cub
```

## 🐛 Troubleshooting

### Common Issues

1. **Build fails with OpenGL errors:**
   ```bash
   # Install OpenGL development libraries
   sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
   ```

2. **MLX42 compilation fails:**
   ```bash
   # Clean and rebuild
   make fclean
   make
   ```

3. **Game crashes on startup:**
   - Ensure map file exists and is properly formatted
   - Check that texture files are present in the specified paths

### Debug Mode

Compile with debug flags for troubleshooting:

```bash
make CFLAGS="-Wall -Wextra -Werror -g"
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 License

This project is part of the 42 School curriculum. Please respect the academic integrity policies of your institution.

## 🙏 Acknowledgments

- **42 School** - For the project specification and educational framework
- **MLX42** - Modern graphics library by Codam Coding College
- **MEDWARDS ART** - For providing game assets and textures
- **Classic Wolfenstein 3D** - For inspiration and raycasting techniques

## 📞 Contact

- **Authors**: omartela, mpellegr
- **Institution**: 42 School / Hive Helsinki
- **Project Repository**: [https://github.com/omartela/cube3D](https://github.com/omartela/cube3D)

---

*Built with ❤️ using C and lots of trigonometry*
