const Switchbot = require('node-switchbot');
const switchbot = new Switchbot();
switchbot
  .discover({ model: "H", quick: true })
  .then((device_list) => {
    return device_list[0].turnOff();
  })
  .then(() => {
    console.log("Done.");
  })
  .catch((error) => {
    console.error(error);
  });
