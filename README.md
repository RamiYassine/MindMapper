# MindMapper

MindMapper is a simple console-based C++ application that helps organize ideas and the thoughts that contribute to them.

Users can create ideas, add or remove thoughts, mark ideas as completed, and save or load their progress from disk. The program demonstrates custom data structures, dynamic memory management, and JSON serialization.

## Build and Run

Compile using cmake:
$ cmake -S . -B build
$ cd build
$ make
$ ./mindmapper

## Technologies

- C++
- Smart pointers (std::shared_ptr, std::unique_ptr)
- JSON serialization using nlohmann/json

## Learning Goals

This project was built to practice:

- Data structures
- Memory management
- Object-oriented design
- File serialization

## Screenshots / terminal example

<img width="543" height="708" alt="image" src="https://github.com/user-attachments/assets/04a88a1d-2763-4e50-a1d1-d456fbf44eeb" />

## Future Improvements

- List all existing save files by filename
- Export ideas to different formats
- Add timestamps to ideas
- Improve console UI

<!-- 
- Create ideas with a custom title
- Add and remove thoughts that build an idea
- View the full trail of thoughts for an idea
- Mark ideas as completed
- Save and load sessions using JSON
- Traverse and manage ideas through a console interface

-->
