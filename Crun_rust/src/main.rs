
fn main() {
    println!("Hello world!")
}

fn get_path_to_binary() -> Result<String, Box<dyn std::error::Error>> {
   let mut path_to_binary = String::new();
   let relative_path = "build/.cmake/api/v1/reply/";
   for entry in glob::glob(&format!("{relative_path}index-*.json"))? {
        let path = entry?;
        let index_raw = std::fs::read_to_string(path)?;
        let parsed: serde_json::Value = serde_json::from_str(&index_raw)?;
        let codemodel_path =  relative_path + parsed["reply"]["codemodel-v2"]["jsonFile"]
            .to_string();
        // target;
       let codemodel_raw = std::fs::read_to_string(codemodel_path)?;
       let parsed: serde_json::Value = serde_json::from_str(&codemodel_raw)?;
       path_to_binary += parsed["paths"]["build"].as_str().unwrap();
       break;
   }
   path_to_binary += "/";
   for entry in glob::glob(&format!("{relative_path}target-*.json"))? {
       let path = entry?;
       let target_raw = std::fs::read_to_string(path)?;
       let parsed: serde_json::Value = serde_json::from_str(&target_raw)?;
       path_to_binary += parsed["artifacts"][0]["path"].as_str().unwrap();
       break;
   }
    Ok(path_to_binary)
}
