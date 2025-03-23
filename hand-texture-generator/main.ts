import sharp from "sharp";
import { readFile } from "fs/promises";

async function generateMapTexture() {
  const diffuseData = await readFile("../output/hand.raw");
  const uvMapData = await readFile("../output/uv-map.raw");

  const uvMapBuffer = new Uint16Array(uvMapData.buffer);
  const diffuseBuffer = new Uint16Array(diffuseData.buffer);

  // this is the output of the texture dimensions buffer
  const oW = 2048;
  const oH = 2048;
  const outputBuffer = Buffer.alloc(oW * oH * 4);

  for (let x = 0; x < 3840; x++) {
    for (let y = 0; y < 2160; y++) {
      const p = getPixelAtRGBA(uvMapBuffer, x, y, 3840, 2160);
      const { r, g, b } = getPixelAtRGBA(diffuseBuffer, x, y, 3840, 2160);

      const oX = Math.round((p.r / 65535) * oW);
      const oY = Math.round((p.g / 65535) * oH);

      const i = oY * oW * 4 + oX * 4;

      outputBuffer[i] = r;
      outputBuffer[i + 1] = g;
      outputBuffer[i + 2] = b;
      outputBuffer[i + 3] = 65535;
    }
  }

  await sharp(outputBuffer, {
    raw: { width: oW, height: oH, channels: 4 },
  }).toFile("../output/output.png");
}

function getPixelAtRGB(
  data: Uint16Array | Uint8Array,
  x: number,
  y: number,
  w: number,
  h: number
) {
  const i = y * w * 3 + x * 3;

  return {
    r: data[i],
    g: data[i + 1],
    b: data[i + 2],
  };
}

function getPixelAtRGBA(
  data: Uint16Array | Uint8Array,
  x: number,
  y: number,
  w: number,
  h: number
) {
  const i = y * w * 4 + x * 4;

  return {
    r: data[i],
    g: data[i + 1],
    b: data[i + 2],
    a: data[i + 3],
  };
}

//generateUVTexture();
generateMapTexture();
