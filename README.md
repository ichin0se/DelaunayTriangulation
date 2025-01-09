## DelaunayTriangulation

Houdini の CVex で DelaunayTriangulation を実装したリポジトリ

## Enviroment
Houdini: 20.5.278 (Production Build) Education Edition

## Directory Structure
.\
└── vex\
│    ├── CVex\
│    │    ├── Legalize.vex\
│    │    └── Legalize.vfl\
│    └── include\
│          ├── edge.h\
│          └── utility.h\
└── 3dDelaunay.hipnc

## Installation
1. Place repository root where $HOUDINI_PATH goes.
2. Set up Houdini Enviroment in the shell.
3. "cd repositoryRoot/vex/CVex"
4. Compile by "vcc ./legalize.vfl"
5. Open hip file.
