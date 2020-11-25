var AWS = require('aws-sdk');

// 配置
const endpoint = new AWS.Endpoint('http://172.29.254.38')
const s3 = new AWS.S3({
  accessKeyId: "96145E5247AJTTMVH6IJ",
  secretAccessKey: "3QBvZN6Lg4h9nEaSZPT2McwcK5NzR497TARzqAxs",
  hostPrefixEnabled: false, //是否将请求参数编组为主机名的前缀。
  endpoint,
  s3ForcePathStyle: true  //是否对S3对象强制使用路径样式URL
})



//创建bucket---ok
// var params = {
//     Bucket: 'room', /* required */
//     CreateBucketConfiguration:{LocationConstraint:""} //注意该参数必须设置为空字符串
// };
// s3.createBucket(params,function(err,data){
//     console.log(`err:${err}`);
//     console.log(`data:${JSON.stringify(data)}`);
// });


//删除bucket--ok
// s3.deleteBucket({Bucket:"room"},function(err,data){
//     console.log(JSON.stringify(err));
//     console.log(data);
// });



//列出bucket--ok
// s3.listBuckets(function(err,data){
//     if(err){
//         console.log("err:"+err);
//     }
//     console.log(JSON.stringify(data));
// });

//列出obj--ok
// s3.listObjects({Bucket:"new-bucket-e411ade5"}, function (err, data) {
//     if (err) {
//         console.log("Error", err);
//     } else {
//         let objs = [];
//         let cont = data.Contents;
//         for (let key in cont) {
//             obj_name = cont[key].Key;
//             // console.log(obj_name);
//             objs.push(obj_name);
//         }
//         console.log(objs);
//     }
// });


//上传文件--ok
// var fs = require("fs");
// var fs_data = fs.readFileSync('./lin.aac');
// // console.log("同步读取: " + fs_data.toString());
// params = {
//     Bucket: "new-bucket-e411ade5",
//     Body: fs_data,
//     Key: "lin.aac",
// }
// s3.putObject(params, function (err, data) {
//     if (err) {
//         console.log("Error", err);
//     } else {
 
//         console.log("data", data)
//     }
// })


//下载文件 ---ok
// var fs = require("fs");
// let params = {
//     Bucket: "new-bucket-e411ade5",
//     Key: "lin.aac"
// }
// s3.getObject(params, function (err, data) {
//     if (err) {
 
//         console.log("Error", err);
//     } else {
 
//         console.log("data", data.Body)
//         fs.writeFileSync('write.aac', data.Body);
//     }
// });


