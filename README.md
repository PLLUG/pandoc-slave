# pandoc-slave
Special module to run Pandoc application with different parameters in Qt projects.This project was designed
as a part of [Pllug Presentetion System 2](https://github.com/PLLUG/pllug-presentation-system-2) project.
Hovewer you can use it in any other projects.

## Dependencies
In order to use this project you must have installed pandoc in system. Read
[pandoc official documentation](http://pandoc.org/installing.html) how do this. After installind copy pandoc.exe
file to pandoc folder. This instance use for runing project.

## Usage as submodule
Important step for use project, understanding how
[working with submoduls](https://github.com/blog/2104-working-with-submodules) in git.

## Getting started
First of all you need build parameters line using `ParamsBuilser` class. This class provide special functionality to combining various parameters and build one complexity parameters string. Let's build parameters line for convert markdown input file `input.md` into output HTML file `output.html`:
```c++
use namespace PandocSlave;
...
ParamsBuilder builder;

builder.addParam(ParamsBuilder::empty, "path/to/input.md");
builder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
builder.addParam(ParamsBuider::output, "path/to/output.html");

qDebug() << builder.toString();
```
This code produce and print following parameters string ([see here for more information about parameters](http://pandoc.org/installing.html)):
```
path/to/input.md -f markdown -t html -o path/to/output.html
```
Next step, use `builder` instance in `PandocRunner` class. For example:
```c++
use
```

