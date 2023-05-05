const express = require('express');
const {exec} = require("child_process");
const router = express.Router();

/* GET users listing. */
router.get('/', async function (req, res, next) {
    let responce = {
        "opt": req.query.toDOrNotToD
    }
    if (responce["opt"] === "YES") {
      const process = exec(`python ./test.py`);
      process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
        res.send(data)
      });
      process.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
      });
      await new Promise(r => setTimeout(r, 500));
      res.redirect(req.get('referer'));
    }

});


const getVoltage = async (res) => {
    const process = exec("python ./test.py");
    process.stdout.on('data', (data, res) => {
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
    });
    await new Promise(r => setTimeout(r, 500));
};


module.exports = router;
