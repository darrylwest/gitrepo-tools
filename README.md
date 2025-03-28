# CPP Git Repo Tools

```ascii
 _______ __ __     ______                      _______               __        
|     __|__|  |_  |   __ \.-----.-----.-----. |_     _|.-----.-----.|  |.-----.
|    |  |  |   _| |      <|  -__|  _  |  _  |   |   |  |  _  |  _  ||  ||__ --|
|_______|__|____| |___|__||_____|   __|_____|   |___|  |_____|_____||__||_____|
                                |__|                                           
```

Tools to monitor and manage mutiple repos on a single machine.

## Features

* collect a database of all repos on system
* report status, branch, location 
* send git commands to multiple repos

 
## Installation Requirements

* spdlog
* Catch2
* quickkv
* domainkeys

## File Structure

```
git-repo-tools
  | 
  └─include
    ├── gitrepo
    │   └── tools.hpp
    └── vendor
    ├── ansi_colors.hpp
    ├── cxxopts.hpp
    └── perftimer.hpp
  └─src
    └── main.cpp
  └─tests
    └── main_unit.cpp
```

## Use

_TDB_

## Future

_After the initial concepts are flushed out, it will be time to ingegrate with libgit2 for extended operations.  This may or maynot happen..._

###### 2025.03.28 | dpw
