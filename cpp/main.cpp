#include <iostream>
#include <aws/s3/S3Client.h>
#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/ListObjectsRequest.h>

#include <aws/s3/model/PutObjectRequest.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>


#include <aws/s3/model/GetObjectRequest.h>


using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace std;


/*
获取bucket列表 
*/

void  listBuckets(S3Client& client)
{
	auto response = client.ListBuckets();

	if (response.IsSuccess())
	{
		auto buckets = response.GetResult().GetBuckets();
		for (auto iter = buckets.begin(); iter != buckets.end(); ++iter)
		{
			cout << iter->GetName() << "\t" << iter->GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601) << endl;
		}
	} else
	{
		cout << "Err name:"<< response.GetError().GetExceptionName() << endl;
		cout << "Err msg:["<< response.GetError().GetMessage() <<"]"<< endl;
	}
	
}

/*
获取object列表
*/
void listObjects(S3Client& client)
{

	Aws::S3::Model::ListObjectsRequest   request;
	request.SetBucket("new-bucket-e411ade5");
	
	auto  response = client.ListObjects(request);
	if(response.IsSuccess())
	{
		auto contents  = response.GetResult().GetContents();

		for (auto iter = contents.begin(); iter != contents.end(); ++iter)
		{
			cout <<"key: "<< iter->GetKey() <<" size:  "<< iter->GetSize() << endl;
		}
	}else
	{
		cout << "Err name:"<< response.GetError().GetExceptionName() << endl;
		cout << "Err msg:["<< response.GetError().GetMessage() <<"]"<< endl;
	}
	
}


/*
上传文件
*/

void putObject(S3Client& client)
{
	Model::PutObjectRequest  request;
	request.SetBucket("room");
	//request.SetExpires(Aws :: Utils :: DateTime && value);//设置超时
	request.SetKey("lin.aac");


    std::shared_ptr<Aws::IOStream> input_data = 
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag", 
            "./lin.aac", 
            std::ios_base::in | std::ios_base::binary);
	
	request.SetBody(input_data);

	auto result  =client.PutObject(request);

	if (result.IsSuccess()) 
	{
		std::cout << "Added object  succed!" <<  endl; 
	}
	else 
	{
		cout << "Error: PutObject: " <<  endl;
	}

}


/*
下载文件
*/
void  getObject(S3Client& client)
{
	Aws::S3::Model::GetObjectRequest object_request;
	object_request.SetBucket("room");
	object_request.SetKey("lin.aac");
	
	auto get_object_outcome =  client.GetObject(object_request);
	if (get_object_outcome.IsSuccess())
	{
	 		 
		Aws::OFStream local_file;
		local_file.open("get.aac", std::ios::out | std::ios::binary);
		local_file << get_object_outcome.GetResult().GetBody().rdbuf();
		std::cout << "Done!" << std::endl;
	}
	else
	{
		std::cout << "GetObject error: " <<
			get_object_outcome.GetError().GetExceptionName() << " " <<
			get_object_outcome.GetError().GetMessage() << std::endl;
	}







	
}


int main(int argc, char* argv[]) {
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration cfg;
    cfg.endpointOverride = "172.29.254.38";  // S3服务器地址和端口
    cfg.scheme = Aws::Http::Scheme::HTTP;
    cfg.verifySSL = false;
	cfg.region =  "demo";
	//cfg.enableHostPrefixInjection =  true;

    Aws::Auth::AWSCredentials cred("96145E5247AJTTMVH6IJ", "3QBvZN6Lg4h9nEaSZPT2McwcK5NzR497TARzqAxs");  // 认证的Key
	S3Client client(cred, cfg,Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never,false);  //一定要useVirtualAddressing 设置为false
	//listBuckets(client);
	//listObjects(client);
	//putObject(client);
	getObject(client);

    Aws::ShutdownAPI(options);
    return 0;
}
