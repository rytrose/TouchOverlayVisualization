# TouchOverlayVisualization
To set up the Xcode project:
* `cd` into `/cpp/oscpack`
* run `make install`
  * this should create a file called `liboscpack.so.1.1.0`
* In Xcode, click on the project in the left-hand browser and click on `Build Phases`
* In `Link Binary With Libraries`, add the path to `liboscpack.so.1.1.0`

To run the visualization:
* Run the Xcode project
* `cd` into `js` and run `npm install`
  * Confirmed working in Node v8.9.4, doesn't work in all prior versions of Node
* Run `node .`
* Navigate to `localhost:3000` in your most favorite web browser
