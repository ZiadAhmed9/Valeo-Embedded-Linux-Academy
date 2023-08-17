By : **Ziad Ahmed Ibrahim**
Requirements: build a project using Cmake

---

## Project tree
![[Pasted image 20230817133816.png]]

## Building steps
### 1) generate the makefile
 - execute `cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./build/`
![[Pasted image 20230817134303.png]]

### 2) Build the project
- `make install`
![[Pasted image 20230817134501.png]]

### 3) Execute the binary
![[Pasted image 20230817134540.png]]
![[Pasted image 20230817134641.png]]

