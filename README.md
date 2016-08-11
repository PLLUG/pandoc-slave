# pandoc-slave
Special module to run Pandoc application with different parameters in Qt projects.This project was designed
as a part of [Pllug Presentetion System 2](https://github.com/PLLUG/pllug-presentation-system-2) project.
Hovewer you can use it in any other projects.

## Dependencies
In order to use this project you must have installed pandoc in system. Read
[pandoc official documentation](http://pandoc.org/installing.html) how do this. After installind copy pandoc.exe
file to `pandoc` folder. This instance use for runing project.

## Usage as submodule
Important step for use project, understanding how
[working with submoduls](https://github.com/blog/2104-working-with-submodules) in git.

## Getting started
First of all you need build parameters line using `ParamsBuilser` class. This class provide special functionality to combining various parameters and build one complexity parameters string. Let's build parameters line for convert markdown input file `input.md` into output HTML file `output.html`:
```c++
using namespace PandocSlave;
...
ParamsBuilder builder;

builder.addParam(ParamsBuilder::empty, "path/to/input.md");
builder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
builder.addParam(ParamsBuider::output, "path/to/output.html");

qDebug() << builder.toString();
```
This code produce and print following parameters string ([see here for more information about pandoc parameters](http://pandoc.org/installing.html)):
```
path/to/input.md -f markdown -t html -o path/to/output.html
```
Next step, use `builder` instance in `PandocRunner` class. For example:
```c++
using namespace PandocSlave;
...
QString pandocExePath = "path/to/pandoc.exe";

PandocRunner runner(pandocExePath, builder.params());
runner.run();
```

### Supported formats
| Format        | Describe      |
| ------------- | ------------- |
|`ParamsBuilder::Markdown`|Simple markdown|
|`ParamsBuilder::Markdown_Github`|Github markdown|
|`ParamsBuilder::HTML`|HTML format|
|`ParamsBuilder::Json`|Json format|


### Supported pandoc parameters
| Parameter | Describe |
| --------- | -------- |
|`ParamsBuilder::empty`|Use for presents parameter without key.|
|`ParamsBuilder::from`|Presentation of `-f` pandoc parameter.|
|`ParamsBuilder::to`|Presentation of `-t` pandoc parameter.|
|`ParamsBuilder::output`|Presentation of `-o` pandoc parameter.|
|`ParamsBuilder::standalone`|Presentation of `-s` pandoc parameter.|
|`ParamsBuilder::template_file`|Presentation of `--template` pandoc parameters.|

### Pandoc template engine
Imagine we have following `input.md` file with content:
```
# Header
```
We want convert this file into `html` format using pandoc template engine.
First of all we must have some template, for example, `template.html`:
```html
<root>
$body$
</root>
```
If we run following command:
```
pandoc input.md -f markdown -t html --template template.html
```
we get output content:
```html
<root>
<h1 id="header">Header</h1>
</root>
```

`$body$` template variable is predefined pandoc variable.
But, we can define own variables. Value for this variables we can pass
throught command line using parameter `--metadata`. Let's construct
`ParamsBuilder` instance for using template:
```c++
using namespace PandocSlave;

ParamsBuilder builder;
builder.addParam(ParamsBuilder::empty, "path/to/input.md");
builder.addParam(ParamsBuilder::from, ParamsBuilders::Markdown);
builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
builder.addParam(ParamsBuilder::template_file, "path/to/template.html");
builder.addParam(ParamsBuilder::metadata, "author:\"Author Name\"");
```

In example above `input.md` file:
```
# Header
```
and `template.html` file:
```html
<root author="$author$">
$body$
</root>
```

Happy codding.
