import { authorize } from "./GoogleSheetsAuth";



// Used to run authorize flow manually. Running from npm run doesn't work - it starts non-interactive session.
// Run using npx ts-node src/ts/know-your-knowledge-core/auth/auth-setup-helper.ts
authorize()
  .then(() => console.log("✅ Token saved successfully."))
  .catch(console.error);
