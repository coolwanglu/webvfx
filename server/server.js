const puppeteer = require('puppeteer');
const ipc = require('./build/Release/ipc');

(async() => {
  ipc.init();

  const browser = await puppeteer.connect({
    browserURL: 'http://localhost:8888',
    defaultViewport: {
      width: 800,
      height: 600,
    },
  });
  const page = await browser.newPage();

  let webvfx_init = new Promise(resolve => resolve());

  await page.goto('http://localhost:9000/overlay/overlay_PG.html');

  page.on('console', function(msg) {
    if (msg.text == 'WEBVFX INIT') {
      webvfx_init.resolve();
    }
  });

  await webvfx_init;

  while(true) {
    var render_time = ipc.receive_request();
  
    await page.evaluate(render_time => {
      webvfx.render(render_time);
    }, render_time);

    const screenshot = await page.screenshot({
      type: 'png',
      omitBackground: 'true',
      encoding: 'binary',
    });

    ipc.save_screenshot(screenshot);
    ipc.send_response(screenshot.length);
  }

})();
