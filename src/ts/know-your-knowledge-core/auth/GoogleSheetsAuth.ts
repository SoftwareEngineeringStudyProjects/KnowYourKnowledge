import { google } from "googleapis";
import { OAuth2Client } from "google-auth-library";
import * as fs from "fs";
import * as path from "path";
import readline from "readline";

const TOKEN_PATH = path.join(process.cwd(), "token.json");
const CREDENTIALS_PATH = path.join(process.cwd(), "credentials.json");

/*
Go to the Google Cloud Console https://console.cloud.google.com/apis/credentials
If needed, choose or create correct project
If needed, configure consent screen for the project (specify app name, support e-mail, audience type - internal or external, contact e-mail). If using external audience, add test user emails.
Create an OAuth 2.0 Client ID (type = “Desktop App”). WARNING: need to download client secrets immediately, or create a new client secret - starting from April 2025, Google disabled viewing or downloading previous client secrets. https://support.google.com/cloud/answer/15549257#client-secret-hashing
Download the file as credentials.json and place it in your project root.
Need to create token.json by running authorize(). It will provide link in terminal, need to visit this link in browser and authorize Know Your Knowledge app. It then redirects to an URL http://localhost/?code=<something>, the URL doesn't open, but can copy code and paste into terminal.


*/


/**
 * Load saved credentials if they exist.
 */
function loadSavedCredentialsIfExist() {
  try {
    const content = fs.readFileSync(TOKEN_PATH, "utf8");
    const credentials = JSON.parse(content);
    return google.auth.fromJSON(credentials);
  } catch {
    return null;
  }
}

/**
 * Save credentials to disk.
 */
function saveCredentials(client: any) {
  const content = fs.readFileSync(CREDENTIALS_PATH, "utf8");
  const keys = JSON.parse(content);
  const key = keys.installed || keys.web;
  const payload = JSON.stringify({
    type: "authorized_user",
    client_id: key.client_id,
    client_secret: key.client_secret,
    refresh_token: client.credentials.refresh_token,
  });
  fs.writeFileSync(TOKEN_PATH, payload);
}

/**
 * Get an authenticated OAuth2 client.
 */
export async function authorize()  { //: Promise<OAuth2Client>
  let client = loadSavedCredentialsIfExist();
  if (client) return client;

  const content = fs.readFileSync(CREDENTIALS_PATH, "utf8");
  const credentials = JSON.parse(content);
  const { client_secret, client_id, redirect_uris } = credentials.installed;
  const oAuth2Client = new google.auth.OAuth2(client_id, client_secret, redirect_uris[0]);

  const authUrl = oAuth2Client.generateAuthUrl({
    access_type: "offline",
    scope: ["https://www.googleapis.com/auth/spreadsheets"],
  });
  console.log("🔗 Authorize this app by visiting this URL:\n", authUrl);

  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  const code = await new Promise<string>(resolve => {
    rl.question("Enter the code from that page here: ", resolve);
  });

  rl.close();

  const tokenResponse = await oAuth2Client.getToken(code);
  oAuth2Client.setCredentials(tokenResponse.tokens);
  saveCredentials(oAuth2Client);

  return oAuth2Client;
}
