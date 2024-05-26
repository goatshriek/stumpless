# Copyright 2024 Joel E. Anderson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# replaces markdown tags with html entities
sed -i -E "s/:albania:/\&#127462;\&#127473;/g" $1
sed -i -E "s/:brazil:/\&#127463;\&#127479;/g" $1
sed -i -E "s/:bulgaria:/\&#127463;\&#127468;/g" $1
sed -i -E "s/:cn:/\&#127464;\&#127475;/g" $1
sed -i -E "s/:czech_republic:/\&#127464;\&#127487;/g" $1
sed -i -E "s/:de:/\&#127465;\&#127466;/g" $1
sed -i -E "s/:denmark:/\&#127465;\&#127472;/g" $1
sed -i -E "s/:es:/\&#127466;\&#127480;/g" $1
sed -i -E "s/:fr:/\&#127467;\&#127479;/g" $1
sed -i -E "s/:greece:/\&#127468;\&#127479;/g" $1
sed -i -E "s/:hungary:/\&#127469;\&#127482;/g" $1
sed -i -E "s/:india:/\&#127470;\&#127475;/g" $1
sed -i -E "s/:israel:/\&#127470;\&#127473;/g" $1
sed -i -E "s/:it:/\&#127470;\&#127481;/g" $1
sed -i -E "s/:jp:/\&#127471;\&#127477;/g" $1
sed -i -E "s/:kenya:/\&#127472;\&#127466;/g" $1
sed -i -E "s/:poland:/\&#127477;\&#127473;/g" $1
sed -i -E "s/:slovakia:/\&#127480;\&#127472;/g" $1
sed -i -E "s/:sri_lanka:/\&#127473;\&#127472;/g" $1
sed -i -E "s/:sweden:/\&#127480;\&#127466;/g" $1
sed -i -E "s/:tr:/\&#127481;\&#127479;/g" $1
sed -i -E "s/:us:/\&#127482;\&#127480;/g" $1
