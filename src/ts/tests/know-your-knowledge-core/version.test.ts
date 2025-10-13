import { getVersion } from "../../know-your-knowledge-core/version";

describe("getVersion", () => {
  it("should return the current version", () => {
    expect(getVersion()).toBe("0.0.1");
  });
});
