#include <iostream>
#include <string>
#include <sstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

bool isLiteralInt(const std::string& str) {
  std::istringstream iss(str);
  int value;
  iss >> value;
  // Check if the entire string was consumed and no error occurred during conversion
  return !iss.fail() && iss.eof();
}

int main() {
  // json simple = json::parse(R"(
  //   {
  //   "products": [
  //     {
  //     "id": 1,
  //     "title": "iPhone 9",
  //     "description": "An apple mobile which is nothing like apple",
  //     "price": 549,
  //     "discountPercentage": 12.96,
  //     "rating": 4.69,
  //     "stock": 94,
  //     "brand": "Apple",
  //     "category": "smartphones",
  //     "thumbnail": "https://cdn.dummyjson.com/product-images/1/thumbnail.jpg",
  //     "images": [
  //       "https://cdn.dummyjson.com/product-images/1/1.jpg",
  //       "https://cdn.dummyjson.com/product-images/1/2.jpg",
  //       "https://cdn.dummyjson.com/product-images/1/3.jpg",
  //       "https://cdn.dummyjson.com/product-images/1/4.jpg",
  //       "https://cdn.dummyjson.com/product-images/1/thumbnail.jpg"
  //     ]
  //     },
  //     {
  //     "id": 2,
  //     "title": "iPhone X",
  //     "description": "SIM-Free, Model A19211 6.5-inch Super Retina HD display with OLED technology A12 Bionic chip with ...",
  //     "price": 899,
  //     "discountPercentage": 17.94,
  //     "rating": 4.44,
  //     "stock": 34,
  //     "brand": "Apple",
  //     "category": "smartphones",
  //     "thumbnail": "https://cdn.dummyjson.com/product-images/2/thumbnail.jpg",
  //     "images": [
  //       "https://cdn.dummyjson.com/product-images/2/1.jpg",
  //       "https://cdn.dummyjson.com/product-images/2/2.jpg",
  //       "https://cdn.dummyjson.com/product-images/2/3.jpg",
  //       "https://cdn.dummyjson.com/product-images/2/thumbnail.jpg"
  //     ]
  //     }
  //   ],
  //   "total": 100
  //   }
  // )");

  // json temp = simple["products"];
  // json temp2 = temp[std::stoi("0")];
  // json temp3 = temp2["title"];
  // std::cout << temp3.dump(2) << std::endl;

  json simple = json::parse(R"(
  [
    {
      "sha": "ed8f7154f4e3e0a8b01e6778de2633aabbb623f8",
      "node_id": "C_kwDOAE3WVdoAKGVkOGY3MTU0ZjRlM2UwYThiMDFlNjc3OGRlMjYzM2FhYmJiNjIzZjg",
      "commit": {
        "author": {
          "name": "sheepster",
          "email": "omer531998@gmail.com",
          "date": "2024-05-01T15:56:48Z"
        },
        "committer": {
          "name": "GitHub",
          "email": "noreply@github.com",
          "date": "2024-05-01T15:56:48Z"
        },
        "message": "doc(readme): Fix docker run with mounted volume command (#3105)\n\nCo-authored-by: Sheepster <sheepstert>",
        "tree": {
          "sha": "f236e53f145461c4462d5ac5c0525bbe1514a7cd",
          "url": "https://api.github.com/repos/jqlang/jq/git/trees/f236e53f145461c4462d5ac5c0525bbe1514a7cd"
        },
        "url": "https://api.github.com/repos/jqlang/jq/git/commits/ed8f7154f4e3e0a8b01e6778de2633aabbb623f8",
        "comment_count": 0,
        "verification": {
          "verified": true,
          "reason": "valid",
          "signature": "-----BEGIN PGP SIGNATURE-----\n\nwsFcBAABCAAQBQJmMmZACRC1aQ7uu5UhlAAABAYQABSYTKbXvfjMPd9P3wc8GAPp\nHlejQ83dcaLHULVt5aOk20k7m5joV0FN8xJ5vl7e47HSEFLcRhF5NVaNIjoR3a3L\nD5pFqMpYti1bRER26W29iHMJY1h7AScWlhi3GLG8gYPWhvVGzDcFVQX6MF9b+tnd\naJLcXNffB0u6mbGyTtKChwiIYJchMmCrbWww8Lz7zyjEUdHOODheJKJwhH6xHDno\nyeYdJKAbJclP5IYB3kKQ+Xo1i+E2DWF4cEJ9mgRtOfisj34Stqt2vpFAXZVHt0QZ\nikP56sCrfZq/jA1WEdyjqefomqylATydthap9ZIzbLJ+uHUYeVq63uUQwZ+rh3I0\nprjAwUIZ459896gMsrtq4bCs9MC5HtFaKby0ddUzQRHMULPq8h5Qqfic1XyWw3uv\npqejiySAFwxav7EwsYkVN/z34DHIuvw13BDQO9/Rq2ChHht3sFsaMvbkfTem9jqT\nWgUm6vqadaKtZ8QKOi0EkxoGlnX+AEFeYUFmZKIQT1/w1xGs0KDVVo7LEL12OG9I\nVPxiVnxEQBw4/vqcM4naSbIsM1ztPMw8dJAcdJ1cuXD19v98cGGlZZvsdivEAgV0\n3FdM+RUQjLBMR6B2mNzxw/tRd3F/0Ubf0fUIHJSMYC3dxG75G0P1TWbNq4W/vx4z\nVmKEpih8C238EHDuiYkI\n=24u/\n-----END PGP SIGNATURE-----\n",
          "payload": "tree f236e53f145461c4462d5ac5c0525bbe1514a7cd\nparent 9afc450930b19ca179e6ef4e744853a94a7b72cf\nauthor sheepster <omer531998@gmail.com> 1714579008 +0300\ncommitter GitHub <noreply@github.com> 1714579008 +0200\n\ndoc(readme): Fix docker run with mounted volume command (#3105)\n\nCo-authored-by: Sheepster <sheepstert>"
        }
      },
      "url": "https://api.github.com/repos/jqlang/jq/commits/ed8f7154f4e3e0a8b01e6778de2633aabbb623f8",
      "html_url": "https://github.com/jqlang/jq/commit/ed8f7154f4e3e0a8b01e6778de2633aabbb623f8",
      "comments_url": "https://api.github.com/repos/jqlang/jq/commits/ed8f7154f4e3e0a8b01e6778de2633aabbb623f8/comments",
      "author": {
        "login": "sheepster1",
        "id": 21146068,
        "node_id": "MDQ6VXNlcjIxMTQ2MDY4",
        "avatar_url": "https://avatars.githubusercontent.com/u/21146068?v=4",
        "gravatar_id": "",
        "url": "https://api.github.com/users/sheepster1",
        "html_url": "https://github.com/sheepster1",
        "followers_url": "https://api.github.com/users/sheepster1/followers",
        "following_url": "https://api.github.com/users/sheepster1/following{/other_user}",
        "gists_url": "https://api.github.com/users/sheepster1/gists{/gist_id}",
        "starred_url": "https://api.github.com/users/sheepster1/starred{/owner}{/repo}",
        "subscriptions_url": "https://api.github.com/users/sheepster1/subscriptions",
        "organizations_url": "https://api.github.com/users/sheepster1/orgs",
        "repos_url": "https://api.github.com/users/sheepster1/repos",
        "events_url": "https://api.github.com/users/sheepster1/events{/privacy}",
        "received_events_url": "https://api.github.com/users/sheepster1/received_events",
        "type": "User",
        "site_admin": false
      },
      "committer": {
        "login": "web-flow",
        "id": 19864447,
        "node_id": "MDQ6VXNlcjE5ODY0NDQ3",
        "avatar_url": "https://avatars.githubusercontent.com/u/19864447?v=4",
        "gravatar_id": "",
        "url": "https://api.github.com/users/web-flow",
        "html_url": "https://github.com/web-flow",
        "followers_url": "https://api.github.com/users/web-flow/followers",
        "following_url": "https://api.github.com/users/web-flow/following{/other_user}",
        "gists_url": "https://api.github.com/users/web-flow/gists{/gist_id}",
        "starred_url": "https://api.github.com/users/web-flow/starred{/owner}{/repo}",
        "subscriptions_url": "https://api.github.com/users/web-flow/subscriptions",
        "organizations_url": "https://api.github.com/users/web-flow/orgs",
        "repos_url": "https://api.github.com/users/web-flow/repos",
        "events_url": "https://api.github.com/users/web-flow/events{/privacy}",
        "received_events_url": "https://api.github.com/users/web-flow/received_events",
        "type": "User",
        "site_admin": false
      },
      "parents": [
        {
          "sha": "9afc450930b19ca179e6ef4e744853a94a7b72cf",
          "url": "https://api.github.com/repos/jqlang/jq/commits/9afc450930b19ca179e6ef4e744853a94a7b72cf",
          "html_url": "https://github.com/jqlang/jq/commit/9afc450930b19ca179e6ef4e744853a94a7b72cf"
        }
      ]
    }
  ]
  )");

  if (isLiteralInt("123")) {
    std::cout << "\"123\" is literal." << std::endl;
  }

  if (isLiteralInt("text")) {
    std::cout << "\"text\" is literal ?" << std::endl;
  }

  // json temp = simple[std::stoi("0")]; if (simple.is_array()) std::cout << "simple is array" << std::endl; 
  // json temp2 = temp["commit"]; if (temp.is_object()) std::cout << "temp is object" << std::endl;
  // json temp3 = temp2["message"]; if (temp2.is_object()) std::cout << "temp2 is object" << std::endl;
  // std::cout << temp3.dump(2) << std::endl;

  return 0;
}