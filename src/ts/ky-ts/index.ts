#!/usr/bin/env node
import { getVersion } from "../know-your-knowledge-core";

const args = process.argv.slice(2);

if (args[0] === "version") {
  console.log(getVersion());
} else {
  console.log("Unknown command. Try: ky-ts version");
}
