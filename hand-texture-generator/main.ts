import sharp from "sharp";
import { readFile } from "fs/promises";

async function generateMapTexture(inputFile: string) {
  // const diffuseData = await readFile("../output/hand_silhouette.raw");
  const diffuseBuffer = await sharp(inputFile).raw().toBuffer();
  const uvMapData = await readFile("../output/hand_uvs.raw");

  const uvMapBuffer = new Uint16Array(uvMapData.buffer);
  // const diffuseBuffer = new Uint16Array(diffuseData.buffer);

  // this is the output of the texture dimensions buffer
  const oW = 1024;
  const oH = 1024;
  const outputBuffer = Buffer.alloc(oW * oH * 4);

  for (let x = 0; x < 3840; x++) {
    for (let y = 0; y < 2160; y++) {
      const p = getPixelAtRGBA(uvMapBuffer, x, y, 3840, 2160);
      const { r, g, b } = getPixelAtRGB(diffuseBuffer, x, y, 3840, 2160);

      const oX = Math.round((p.r / 65535) * oW);
      const oY = Math.round((p.g / 65535) * oH);

      const i = oY * oW * 4 + oX * 4;

      outputBuffer[i] = r;
      outputBuffer[i + 1] = g;
      outputBuffer[i + 2] = b;
      outputBuffer[i + 3] = 65535;
    }
  }

  const outputFilename = `../output/texture_frames/tex_${inputFile.substring(
    inputFile.lastIndexOf("/") + 1
  )}`;

  await sharp(outputBuffer, {
    raw: { width: oW, height: oH, channels: 4 },
  }).toFile(outputFilename);
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

// for (let i = 0; i < 8; i++) {
//   generateMapTexture(`./test_frames/hand_silhouette.raw_${i}.jpg`);
// }

generateMapTexture(`./test_frames/hand_silhouette_blur.jpg`);
