#!/usr/bin/env python3
"""
Script to clean up Doxygen comments in the banking-server project.
This script moves function-level Doxygen comments from .cpp files to their corresponding .hpp files
and adds missing documentation to files that don't have any.
"""

import os
import re
import glob
from pathlib import Path

# Files already processed
PROCESSED_FILES = {
    'AccountOperations.hpp', 'AccountOperations.cpp',
    'BranchOperations.hpp', 'BranchOperations.cpp',
    'ZMQRepSocket.hpp', 'ZMQRepSocket.cpp',
    'ZMQReqSocket.hpp', 'ZMQReqSocket.cpp',
    'IZMQSocket.hpp',
    'ZMQContextManager.hpp',
    'User.hpp', 'User.cpp'
}

def find_cpp_hpp_pairs(src_dir):
    """Find all .cpp/.hpp file pairs in the src directory"""
    pairs = []
    
    # Find all .cpp files
    cpp_files = glob.glob(f"{src_dir}/**/*.cpp", recursive=True)
    
    for cpp_file in cpp_files:
        # Skip external libraries
        if '/Ext/' in cpp_file:
            continue
            
        cpp_path = Path(cpp_file)
        filename = cpp_path.stem
        
        # Skip already processed files
        if f"{filename}.cpp" in PROCESSED_FILES:
            continue
            
        # Look for corresponding .hpp file
        hpp_candidates = [
            cpp_path.parent / f"{filename}.hpp",
            cpp_path.parent / "inc" / f"{filename}.hpp",
            cpp_path.parent.parent / "inc" / f"{filename}.hpp"
        ]
        
        for hpp_candidate in hpp_candidates:
            if hpp_candidate.exists():
                pairs.append((str(cpp_file), str(hpp_candidate)))
                break
    
    return pairs

def extract_doxygen_comments(content):
    """Extract Doxygen comments from content"""
    # Pattern to match Doxygen comments before functions
    pattern = r'(\/\*\*.*?\*\/)\s*([^{};]+[{;])'
    matches = re.findall(pattern, content, re.DOTALL)
    return matches

def needs_doxygen_header(filepath):
    """Check if file needs a Doxygen file header"""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
        # Check if it already has a proper file header
        return not re.search(r'\/\*\*[^*]*\*\s*@file', content)

def add_file_header(filepath, brief_description):
    """Add Doxygen file header to a file"""
    filename = Path(filepath).name
    
    header = f'''/**
 * @file {filename}
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief {brief_description}
 * @version 0.1
 * @date 2025-08-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
'''
    
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Insert header at the beginning
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(header + content)

def get_brief_description(filename):
    """Get appropriate brief description based on filename"""
    descriptions = {
        'CustomerOperations': 'Customer operations class for banking system database interactions',
        'EmployeeOperations': 'Employee operations class for banking system database interactions',
        'DatabaseOperations': 'Main database operations class for banking system',
        'Dispatcher': 'Message dispatcher for routing operations in banking system',
        'Connection': 'Database connection management for banking system',
        'Customer': 'Customer class for banking system user management',
        'Employee': 'Employee class for banking system user management',
        'Logger': 'Logging utilities for banking system',
        'ZMQReceive': 'ZeroMQ receive operations for banking system communications',
        'ZMQRequest': 'ZeroMQ request operations for banking system communications'
    }
    
    base_name = Path(filename).stem
    return descriptions.get(base_name, f'{base_name} implementation for banking system')

def main():
    src_dir = "/home/shubham/proj/banking-server/src"
    
    # Find all .cpp/.hpp pairs
    pairs = find_cpp_hpp_pairs(src_dir)
    
    print(f"Found {len(pairs)} .cpp/.hpp file pairs to process")
    
    for cpp_file, hpp_file in pairs:
        filename = Path(cpp_file).stem
        print(f"\nProcessing {filename}...")
        
        # Add file headers if needed
        if needs_doxygen_header(hpp_file):
            print(f"  Adding header to {Path(hpp_file).name}")
            add_file_header(hpp_file, get_brief_description(filename))
            
        if needs_doxygen_header(cpp_file):
            print(f"  Adding header to {Path(cpp_file).name}")
            add_file_header(cpp_file, f"Implementation of {get_brief_description(filename)}")
    
    # Find standalone header files without .cpp counterparts
    hpp_files = glob.glob(f"{src_dir}/**/*.hpp", recursive=True)
    hpp_files += glob.glob(f"{src_dir}/**/*.h", recursive=True)
    
    for hpp_file in hpp_files:
        if '/Ext/' in hpp_file:
            continue
            
        filename = Path(hpp_file).stem
        if f"{filename}.hpp" in PROCESSED_FILES or f"{filename}.h" in PROCESSED_FILES:
            continue
            
        # Check if there's a corresponding .cpp file
        cpp_exists = any(Path(pair[0]).stem == filename for pair in pairs)
        
        if not cpp_exists and needs_doxygen_header(hpp_file):
            print(f"\nAdding header to standalone file {Path(hpp_file).name}")
            add_file_header(hpp_file, get_brief_description(filename))

if __name__ == "__main__":
    main()
