const SerialPort = require("serialport");
if (process[3] == null) {
    const SerialPort = require('serialport')
    SerialPort.list().then(
      ports => ports.forEach(console.log),
      err => console.error(err)
    )
  return 0;
}
console.log("Connecting");
const sp = new SerialPort(process[3]);
sp.update({
  baudRate: 9600
});
setTimeout(() => {
  let tm = new Date(Date.now());
  let time = tm.getMilliseconds() + tm.getSeconds() * 1000 + tm.getMinutes() * 60 * 1000 + tm.getHours() * 60 * 60 * 1000;
  const buffer = new ArrayBuffer(4);
  const view = new DataView(buffer);
  view.setUint32(1, time);
  sp.write(buffer);
  sp.drain();
  serialport.close();
}, 1000);
